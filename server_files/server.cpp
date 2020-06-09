
#include <iostream>
#include <msgpack.hpp>

#include "server.h"
#include "server_sender_thread.h"

#include "../common_sockets.h"
#include "../common_protocol_message.h"
#include "../common_queue.h"

Server::Server() : running(true) {}



void Server::run() {

    this->skt.bind_and_listen("8080");

    Socket exchange_skt = this->skt.accept_client();

    Queue queue;

    Thread* server_sender = new ServerSenderThread(exchange_skt, queue);
    server_sender->start();


    while (this->running) {
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
        std::cout << "pos X: " << msg.posX << std::endl;
        std::cout << "pos Y: " << msg.posY << std::endl;
        std::cout << "vel X: " << msg.velX << std::endl;
        std::cout << "vel Y: " << msg.velY << std::endl;
    }

}



