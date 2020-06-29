
#include <iostream>
#include <fstream>
#include <msgpack.hpp>

#include "server.h"
#include "server_os_error.h"

#include "server_elf.h"
#include "server_cleric.h"

#define FILE_ERROR_MSG "No se pudo abrir el archivo de configuración"

Server::Server(const char* config_file) : running(true) {
    this->initialize_config(config_file);
    const char* port = config["service"].asCString();
    this->skt.bind_and_listen(port);
}

void Server::run() {
    Socket exchange_skt = this->skt.accept_client();

    Queue queue;

    MapInfo mapInfo;
    CollisionInfo collisionInfo = mapInfo.load();

    msgpack::sbuffer buffer;
    msgpack::packer<msgpack::sbuffer> pk(&buffer);
    pk.pack(mapInfo);
    exchange_skt(buffer);

    int npc_limit = config["npc"]["max_limit"].asInt();
    Thread* npc_thread = new ServerNPCThread(exchange_skt, queue, npc_limit);
    npc_thread->start();

    Thread* server_sender = new ServerSenderThread(exchange_skt, queue);
    server_sender->start();

    Elf race(config);
    Cleric c(config);
    Character character(1, config, c, race, collisionInfo);

    ProtocolTranslator protocol_translator(config);

    while (this->running) {
        // TODO: ClientHandler
        ProtocolMessage received_msg = receive_msg(exchange_skt);
        ProtocolMessage updated_msg = protocol_translator.translate(received_msg, character);
        queue.push(updated_msg);
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
