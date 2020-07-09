#include <iostream>

#include "server_npc_thread.h"
#include "server_processor_thread.h"
#include "../common_files/common_mapinfo.h"



ServerProcessorThread::ServerProcessorThread(
    Queue &receiversQueue,
    ClientManager &clientManager,
    CollisionInfo &collisionInfo,
    Json::Value &config) : receiversQueue(receiversQueue),
                            clientManager(clientManager),
                            collisionInfo(collisionInfo),
                            config(config),
                            running(true) {}




void ServerProcessorThread::run() {

    // int npc_limit = config["npc"]["max_limit"].asInt();
    // Thread* npc_thread = new ServerNPCThread(receiversQueue, npc_limit);
    // npc_thread->start();  // NPC THREAD

    ProtocolTranslator protocol_translator(config, collisionInfo);
    ServerWorld serverWorld;

    NPC* npc = new Spider(config, collisionInfo); // HARDCODEADO
    serverWorld.add(100, npc); 

    std::cout << "NPC CREADO EN: " << std::endl;
    std::cout << "POS X: " << npc->get_body_pos_X() << std::endl;
    std::cout << "POS Y: " << npc->get_body_pos_Y() << std::endl;
    
    while (running) {
        ProtocolMessage received_msg = this->receiversQueue.pop();
        protocol_translator.translate(received_msg, serverWorld);
        if (received_msg.id_message != NOTHING)
           this->clientManager.broadcastMessage(received_msg);

    }
}
