#include <msgpack.hpp>

#include "client_sender_thread.h"
#include "../common_files/common_protocol_message.h"


SenderThread::SenderThread(
    Socket &skt, 
    Queue_2 &queue) : skt(skt), queue(queue), running(true) {}


void SenderThread::run() {

    while (running) {
        MessageToServer msg = this->queue.pop();
        if (msg.event_id == 1)
            continue;
        
        msgpack::sbuffer buffer;
        msgpack::packer<msgpack::sbuffer> pk(&buffer);
        pk.pack(msg);
        if (msg.event_id == 67) {
            running = false;
            std::cout << "MANDANDO ULTIMO MENSAJE" << std::endl;
        }

        this->skt << buffer;
    }

    std::cout << "CERRANDO SENDERS QUEUE" << std::endl;
}
