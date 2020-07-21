

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
        try{
            ProtocolMessage msg = this->messageQueue.pop();
            if (msg.id_message == 68 && msg.id_player == this->client_id)
                running = false;
                
            msgpack::sbuffer message;
            msgpack::packer<msgpack::sbuffer> pk(&message);
            pk.pack(msg);
            skt << message;
        } catch (QueueNotOperatingException& e) {
            this->running = false;
            std::cout << "Exception en el sender thread !" << std::endl;
        }
    }

    std::cout << "Cerrando SENDER THREAD EN EL SERVER" << std::endl;
}
