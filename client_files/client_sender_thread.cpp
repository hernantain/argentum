#include <msgpack.hpp>

#include "client_sender_thread.h"
#include "../common_files/common_protocol_message.h"


SenderThread::SenderThread(
    Socket &skt, 
    Queue &queue) : skt(skt), queue(queue), running(true) {}


void SenderThread::run() {

    while (running) {
        ProtocolMessage msg = this->queue.pop();
        msgpack::sbuffer buffer;
        msgpack::packer<msgpack::sbuffer> pk(&buffer);
        pk.pack(msg);
        if (msg.id_message == 67) {
            running = false;
            std::cout << "MANDANDO ULTIMO MENSAJE" << std::endl;
        }

        this->skt << buffer;
    }

    std::cout << "CERRANDO SENDERS QUEUE" << std::endl;
}
