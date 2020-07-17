#include <iostream>

#include "server_game_loop_thread.h"
#include "server_processor_thread.h"
#include "../common_files/common_mapinfo.h"

#include "server_sword.h"
#include "server_gnarled_staff.h"
#include "server_mana_potion.h"
#include "server_life_potion.h"

ServerProcessorThread::ServerProcessorThread(
    Queue &receiversQueue,
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

    ManaPotion mana(config);
    mana.set_posX(75);
    mana.set_posY(75);
    mana.set_amount(1);
    world.items.push_back(mana);

    LifePotion life(config);
    life.set_posX(125);
    life.set_posY(100);
    life.set_amount(1);
    world.items.push_back(life);
}



void ServerProcessorThread::run() {

    Thread* game_loop = new GameLoopThread(receiversQueue);
    game_loop->start();  // NPC THREAD

    ProtocolTranslator protocol_translator(config, collisionInfo);
    ServerWorld serverWorld;

    this->addingHardcodedItems(serverWorld); // HAY QUE SACAR
    
    while (running) {
        ProtocolMessage received_msg = this->receiversQueue.pop();
        protocol_translator.translate(received_msg, serverWorld);
        if (received_msg.id_message != NOTHING)
           this->clientManager.broadcastMessage(received_msg);
    }
}
