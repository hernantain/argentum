

#include <msgpack.hpp>
#include "server_client_sender_thread.h"




SrvClientSenderThread::SrvClientSenderThread(
    uint16_t client_id, 
    Socket &skt, 
    Queue &messageQueue) : client_id(client_id),
                            skt(skt),
                            messageQueue(messageQueue),
                            running(true) {}



void SrvClientSenderThread::run() {

    std::cout << "SOCKET FD: " << skt.fd << std::endl;
    std::cout << "SENDER TH" << std::endl;
    while (running) {
        ProtocolMessage msg = this->messageQueue.pop();
        std::cout << "ACA NO DEBERIA PASAR" << std::endl;
        msgpack::sbuffer message;
        msgpack::packer<msgpack::sbuffer> pk(&message);
        pk.pack(msg);
        skt(message);
    }
}





