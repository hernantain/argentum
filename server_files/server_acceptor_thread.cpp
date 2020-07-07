
#include <iostream>

#include "server_acceptor_thread.h"
#include "server_processor_thread.h"

#include "../common_files/common_mapinfo.h"
#include "../common_files/common_sockets.h"
#include "../common_files/common_queue.h"



AcceptorThread::AcceptorThread(
    Socket &acceptor_skt, 
    Json::Value &config) : acceptor_skt(acceptor_skt),
                           config(config),
                           running(true),
                           client_id(1) {}



void AcceptorThread::run() {

    Socket client_skt; 
    Queue receiversQueue;

    MapInfo mapInfo;
    CollisionInfo collisionInfo = mapInfo.load();

    msgpack::sbuffer mapBuffer;
    msgpack::packer<msgpack::sbuffer> pk(&mapBuffer);
    pk.pack(mapInfo);


    // // PROCCESSOR THREAD
    Thread* processorThread = new ServerProcessorThread(receiversQueue, clients, collisionInfo, config);
    processorThread->start(); 


    while (this->running) {
        client_skt = this->acceptor_skt.accept_client();
        // IF NOT VALID ....

        client_skt << this->client_id;
        client_skt << mapBuffer;

        SrvClient* client = new SrvClient(client_id, client_skt, receiversQueue);

        // PUSH
        this->clients.push_back(client);

        // CLEAN --> TP 3
        client_id++;
        
    }
}



