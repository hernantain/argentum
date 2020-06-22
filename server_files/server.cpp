
#include <iostream>
#include <fstream>
#include <msgpack.hpp>

#include "server.h"
#include "server_sender_thread.h"
#include "server_os_error.h"

#include "server_character.h"
#include "server_elf.h"
#include "server_cleric.h"

#include "../common_sockets.h"
#include "../common_protocol_message.h"
#include "../common_queue.h"

#define FILE_ERROR_MSG "No se pudo abrir el archivo de configuración"

Server::Server(const char* config_file) : running(true) {
    this->initialize_config(config_file);
    const char* port = config["service"].asCString();
    this->skt.bind_and_listen(port);
    // TODO: Parse players file as we dont have creation window
    // SUGGESTION: use a character factory with its races/clases fctory as well
}

void Server::run() {
    Socket exchange_skt = this->skt.accept_client();

    Queue queue;

    Thread* server_sender = new ServerSenderThread(exchange_skt, queue);
    server_sender->start();

    while (this->running) {
        // TODO: ClientHandler
        Elf race(config);
        Cleric c(config);
        Character character(1, config, c, race);
        
        ProtocolMessage msg;
        msgpack::unpacker pac;
        std::cout << "Corriendo" << std::endl;
        exchange_skt >> pac;
        msgpack::object_handle oh;
        pac.next(oh);
        msgpack::object obj = oh.get();
        obj.convert(msg);

        queue.push(msg);

        std::cout << "ID: " << msg.id << std::endl;
        std::cout << "BODY pos X: " << msg.bodyPosX << std::endl;
        std::cout << "BODY pos Y: " << msg.bodyPosY << std::endl;
        std::cout << "HEAD pos X: " << msg.headPosX << std::endl;
        std::cout << "HEAD pos Y: " << msg.headPosY << std::endl;
        std::cout << "vel X: " << msg.velX << std::endl;
        std::cout << "vel Y: " << msg.velY << std::endl;
    }
}

void Server::initialize_config(const char* config_file) {
    std::ifstream file(config_file);
	if (!file.is_open()) throw OSError(FILE_ERROR_MSG);
    Json::Reader reader;
    reader.parse(file, config);
    file.close();
}
