
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

    msgpack::sbuffer buffer;
    msgpack::packer<msgpack::sbuffer> pk(&buffer);
    pk.pack(mapInfo);
    skt(buffer);

    while (running) {
        ProtocolMessage msg = this->messageQueue.pop();
        msgpack::sbuffer message;
        msgpack::packer<msgpack::sbuffer> pk(&message);
        pk.pack(msg);
        skt(message);
    }
}





