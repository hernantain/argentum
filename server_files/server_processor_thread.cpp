#include <iostream>

#include "server_game_loop_thread.h"
#include "server_processor_thread.h"
#include "../common_files/common_mapinfo.h"

#include "server_sword.h"
#include "server_gnarled_staff.h"


ServerProcessorThread::ServerProcessorThread(
    Queue_2 &receiversQueue,
    ClientManager &clientManager,
    CollisionInfo &collisionInfo,
    Json::Value &config) : receiversQueue(receiversQueue),
                            clientManager(clientManager),
                            collisionInfo(collisionInfo),
                            config(config),
                            running(true) {}



void ServerProcessorThread::addingHardcodedItems(ServerWorld &world) {
    Sword i(config);
    i.set_posX(100);
    i.set_posY(100);
    i.set_amount(1);
    world.items.push_back(i);

    GnarledStaff j(config);
    j.set_posX(200);
    j.set_posY(200);
    j.set_amount(1);
    world.items.push_back(j);

    GnarledStaff z(config);
    z.set_posX(50);
    z.set_posY(50);
    z.set_amount(1);
    world.items.push_back(z);

    Axe axe(config);
    axe.set_posX(100);
    axe.set_posY(200);
    axe.set_amount(1);
    world.items.push_back(axe);

    Hammer hammer(config);
    hammer.set_posX(100);
    hammer.set_posY(300);
    hammer.set_amount(1);
    world.items.push_back(hammer);

    SimpleBow sb(config);
    sb.set_posX(100);
    sb.set_posY(400);
    sb.set_amount(1);
    world.items.push_back(sb);

    Hood hood(config);
    hood.set_posX(100);
    hood.set_posY(500);
    hood.set_amount(1);
    world.items.push_back(hood);

    PlateArmor armor(config);
    armor.set_posX(300);
    armor.set_posY(300);
    armor.set_amount(1);
    world.items.push_back(armor);

    TortoiseShield shield(config);
    shield.set_posX(200);
    shield.set_posY(100);
    shield.set_amount(1);
    world.items.push_back(shield);
}



void ServerProcessorThread::run() {

    Thread* game_loop = new GameLoopThread(receiversQueue);
    game_loop->start();  // NPC THREAD

    ProtocolTranslator protocol_translator(config, collisionInfo);
    ServerWorld serverWorld;

    this->addingHardcodedItems(serverWorld); // HAY QUE SACAR
    
    while (running) {
        ProtocolMessage client_response;
        MessageToServer received_msg = this->receiversQueue.pop();
        protocol_translator.translate(received_msg, client_response, serverWorld);
        if (received_msg.event_id != NOTHING)
           this->clientManager.broadcastMessage(client_response);
    }
}
