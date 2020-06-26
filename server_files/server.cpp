
#include <iostream>
#include <fstream>
#include <msgpack.hpp>

#include "server.h"
#include "server_sender_thread.h"
#include "server_os_error.h"

#include "server_character.h"
#include "server_elf.h"
#include "server_cleric.h"

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

    Elf race(config);
    Cleric c(config);
    Character character(1, config, c, race);

    while (this->running) {
        // TODO: ClientHandler
        
        ProtocolMessage received_msg = receive_msg(exchange_skt);
        // int code = receive_msg.id;
        // ProtocolMessage msg = protocol_translator.translate(msg, character);
        // if (msg) this->queue->push(msg);
        queue.push(received_msg);

        // This is what we receive from client
        std::cout << "ID: " << received_msg.character.id << std::endl;
        std::cout << "BODY pos X: " << received_msg.character.bodyPosX << std::endl;
        std::cout << "BODY pos Y: " << received_msg.character.bodyPosY << std::endl;
        std::cout << "HEAD pos X: " << received_msg.character.headPosX << std::endl;
        std::cout << "HEAD pos Y: " << received_msg.character.headPosY << std::endl;
        std::cout << "vel X: " << received_msg.character.velX << std::endl;
        std::cout << "vel Y: " << received_msg.character.velY << std::endl;
    }
}

void Server::initialize_config(const char* config_file) {
    std::ifstream file(config_file);
	if (!file.is_open()) throw OSError(FILE_ERROR_MSG);
    Json::Reader reader;
    reader.parse(file, config);
    file.close();
}

ProtocolMessage Server::receive_msg(Socket skt) {
    std::cout << "Corriendo" << std::endl;
    ProtocolMessage msg;
    msgpack::unpacker pac;
    skt >> pac;
    msgpack::object_handle oh;
    pac.next(oh);
    msgpack::object obj = oh.get();
    obj.convert(msg);
    return msg;
}
