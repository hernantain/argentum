

#include <msgpack.hpp>
#include "server_sender_thread.h"




SrvClientSenderThread::SrvClientSenderThread(
    uint16_t client_id, 
    Socket &skt, 
    Queue &messageQueue) : client_id(client_id),
                            skt(skt),
                            messageQueue(messageQueue),
                            running(true) {}



void SrvClientSenderThread::run() {

    while (running) {
        ProtocolMessage msg = this->messageQueue.pop();
        msgpack::sbuffer message;
        msgpack::packer<msgpack::sbuffer> pk(&message);
        pk.pack(msg);
        skt(message);
    }
}





