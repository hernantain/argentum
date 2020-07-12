#include <iostream>

#include "server_game_loop_thread.h"
#include "server_processor_thread.h"
#include "../common_files/common_mapinfo.h"

#include "server_sword.h"


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

    Sword i(config);
    i.set_posX(100);
    i.set_posY(100);
    i.set_amount(1);
    serverWorld.items.push_back(i);

    Sword j(config);
    j.set_posX(3100);
    j.set_posY(200);
    j.set_amount(1);
    serverWorld.items.push_back(j);
    
    while (running) {
        ProtocolMessage received_msg = this->receiversQueue.pop();
        protocol_translator.translate(received_msg, serverWorld);
        if (received_msg.id_message != NOTHING)
           this->clientManager.broadcastMessage(received_msg);
    }
}
