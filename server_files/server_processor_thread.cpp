#include <iostream>

#include "server_processor_thread.h"
#include "../common_mapinfo.h"



ServerProcessorThread::ServerProcessorThread(
    Queue &receiversQueue,
    std::vector<SrvClient*> &clients,
    CollisionInfo &collisionInfo,
    Json::Value &config) : receiversQueue(receiversQueue),
                            clients(clients),
                            collisionInfo(collisionInfo),
                            config(config),
                            running(true) {}




void ServerProcessorThread::run() {

    // int npc_limit = config["npc"]["max_limit"].asInt();
    // Thread* npc_thread = new ServerNPCThread(exchange_skt, queue, npc_limit);
    // npc_thread->start();  NPC THREAD

    ProtocolTranslator protocol_translator(config, collisionInfo);
    ServerWorld serverWorld;
    while (running) {

        ProtocolMessage received_msg = this->receiversQueue.pop();
        protocol_translator.translate(received_msg, serverWorld);
        this->broadcastMessage(received_msg);

    }
}



void ServerProcessorThread::broadcastMessage(ProtocolMessage &updated_msg) {
    for (unsigned int i = 0; i < clients.size(); ++i) {
        this->clients[i]->send_message(updated_msg);
    }
}

