
#include <msgpack.hpp>
#include "server_client_sender_thread.h"





SrvClientSenderThread::SrvClientSenderThread(
    uint16_t client_id, 
    Socket &skt, 
    Queue &messageQueue, 
    MapInfo &mapInfo) : client_id(client_id),
                        skt(skt),
                        messageQueue(messageQueue),
                        mapInfo(mapInfo),
                        running(true) {}



void SrvClientSenderThread::run() {


    skt(this->client_id);
    std::cout << "Mandando ID: " << this->client_id << std::endl;
    
    msgpack::sbuffer buffer;
    msgpack::packer<msgpack::sbuffer> pk(&buffer);
    pk.pack(mapInfo);
    skt(buffer);

    std::cout << "Mandando ID y MAPA" << std::endl;
    

    while (running) {
        ProtocolMessage msg = this->messageQueue.pop();
        std::cout << "MSG ID: " << msg.id_message << std::endl;
        msgpack::sbuffer message;
        msgpack::packer<msgpack::sbuffer> pk(&message);
        pk.pack(msg);
        skt(message);
    }
}





