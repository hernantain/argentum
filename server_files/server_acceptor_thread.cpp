
#include "server_acceptor_thread.h"

#include "common_mapinfo.h"
#include "common_sockets.h"
#include "common_queue.h"



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


    // PROCCESSOR THREAD
    Thread* processorThread = new ServerProcessorThread();
    processorThread->start(receiversQueue, clients, collisionInfo, config);



    while (this->running) {
        client_skt = this->acceptor_skt.accept_client();
        // IF NOT VALID ....

        SrvClient client(client_id, client_skt, receiversQueue, mapInfo);

        // PUSH
        this->clients.push_back(client);

        // CLEAN
        client_id++;
    }
}



