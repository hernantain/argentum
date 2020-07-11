#include <iostream>

#include "server_game_loop_thread.h"
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

    Thread* game_loop = new GameLoopThread(receiversQueue);
    game_loop->start();  // NPC THREAD

    ProtocolTranslator protocol_translator(config, collisionInfo);
    ServerWorld serverWorld;
    
    while (running) {
        ProtocolMessage received_msg = this->receiversQueue.pop();
        if (received_msg.id_message == 1)
            continue;
        
        protocol_translator.translate(received_msg, serverWorld);
        if (received_msg.id_message != NOTHING)
           this->clientManager.broadcastMessage(received_msg);
    }
}
