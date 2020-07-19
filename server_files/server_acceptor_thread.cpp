
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
    MessageToServerQueue receiversQueue;

    MapInfo mapInfo;
    CollisionInfo collisionInfo = mapInfo.load();

    msgpack::sbuffer mapBuffer;
    msgpack::packer<msgpack::sbuffer> pk(&mapBuffer);
    pk.pack(mapInfo);


    // PROCCESSOR THREAD
    Thread* processorThread = new ServerProcessorThread(receiversQueue, clientManager, collisionInfo, config);
    processorThread->start(); 


    while (this->running) {
        client_skt = this->acceptor_skt.accept_client();
        // IF NOT VALID ....
        std::cout << "SOCKET FD: " << client_skt.fd << std::endl;

        client_skt << this->client_id;
        client_skt << mapBuffer;

        clientManager.add_client(client_id, client_skt, receiversQueue);

        client_id++;
    }
}



