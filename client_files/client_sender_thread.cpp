#include <msgpack.hpp>

#include "client_sender_thread.h"
#include "../common_protocol_message.h"


SenderThread::SenderThread(
    Socket &skt, 
    Queue &queue) : skt(skt), queue(queue), running(true) {}


void SenderThread::run() {

    while (running) {
        ProtocolMessage msg = this->queue.pop();
        msgpack::sbuffer buffer;
        msgpack::packer<msgpack::sbuffer> pk(&buffer);
        pk.pack(msg);
        
        this->skt(buffer);
    }

}
