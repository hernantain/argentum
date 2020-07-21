
#include "server_game_loop_thread.h"
#include "server_processor_thread.h"
#include "../common_files/common_mapinfo.h"

ServerProcessorThread::ServerProcessorThread(
    MessageToServerQueue &receiversQueue,
    ClientManager &clientManager,
    CollisionInfo &collisionInfo,
    Json::Value &config) : receiversQueue(receiversQueue),
                            clientManager(clientManager),
                            collisionInfo(collisionInfo),
                            config(config),
                            running(true) {}


void ServerProcessorThread::run() {

    ProtocolTranslator protocol_translator(config, collisionInfo);
    ServerWorld serverWorld;
    
    Banker banker(collisionInfo.get_banker_posX(), collisionInfo.get_banker_posY());
    serverWorld.add(banker);

    Priest priest(collisionInfo.get_priest_posX(), collisionInfo.get_priest_posY());
    serverWorld.add(priest);

    GameLoopThread* game_loop = new GameLoopThread(receiversQueue);
    game_loop->start();

    this->addingHardcodedItems(serverWorld); // This might be deleted
    
    while (running) {
        ProtocolMessage client_response;
        try {
            MessageToServer received_msg = this->receiversQueue.pop();
            protocol_translator.translate(received_msg, client_response, serverWorld);
            if (client_response.id_message != NOTHING)
            this->clientManager.broadcastMessage(client_response);
        } catch (QueueNotOperatingException& e) {
            this->running = false;
        }
    }

    game_loop->stop();
    game_loop->join();
    delete game_loop;
}




void ServerProcessorThread::addingHardcodedItems(ServerWorld &world) {

    LeatherArmor leatherArmor(config);
    leatherArmor.set_posX(100);
    leatherArmor.set_posY(10);
    leatherArmor.set_amount(1);
    world.items.push_back(leatherArmor);

    PlateArmor plateArmor(config);
    plateArmor.set_posX(200);
    plateArmor.set_posY(10);
    plateArmor.set_amount(1);
    world.items.push_back(plateArmor);

    BlueRobe blueRobe(config);
    blueRobe.set_posX(300);
    blueRobe.set_posY(10);
    blueRobe.set_amount(1);
    world.items.push_back(blueRobe);

    Hood hood(config);
    hood.set_posX(400);
    hood.set_posY(10);
    hood.set_amount(1);
    world.items.push_back(hood);

    IronHelmet ironHelmet(config);
    ironHelmet.set_posX(500);
    ironHelmet.set_posY(10);
    ironHelmet.set_amount(1);
    world.items.push_back(ironHelmet);

    MagicHat magicHat(config);
    magicHat.set_posX(600);
    magicHat.set_posY(10);
    magicHat.set_amount(1);
    world.items.push_back(magicHat);

    TortoiseShield tortoiseShield(config);
    tortoiseShield.set_posX(700);
    tortoiseShield.set_posY(10);
    tortoiseShield.set_amount(1);
    world.items.push_back(tortoiseShield);

    IronShield ironShield(config);
    ironShield.set_posX(800);
    ironShield.set_posY(10);
    ironShield.set_amount(1);
    world.items.push_back(ironShield);

    Sword sword(config);
    sword.set_posX(900);
    sword.set_posY(10);
    sword.set_amount(1);
    world.items.push_back(sword);

    Axe axe(config);
    axe.set_posX(1000);
    axe.set_posY(10);
    axe.set_amount(1);
    world.items.push_back(axe);

    Hammer hammer(config);
    hammer.set_posX(100);
    hammer.set_posY(90);
    hammer.set_amount(1);
    world.items.push_back(hammer);

    AshStaff ashStaff(config);
    ashStaff.set_posX(200);
    ashStaff.set_posY(90);
    ashStaff.set_amount(1);
    world.items.push_back(ashStaff);

    GnarledStaff gnarledStaff(config);
    gnarledStaff.set_posX(300);
    gnarledStaff.set_posY(90);
    gnarledStaff.set_amount(5);
    world.items.push_back(gnarledStaff);

    CrimpStaff crimpStaff(config);
    crimpStaff.set_posX(400);
    crimpStaff.set_posY(90);
    crimpStaff.set_amount(1);
    world.items.push_back(crimpStaff);

    SimpleBow sb(config);
    sb.set_posX(500);
    sb.set_posY(90);
    sb.set_amount(1);
    world.items.push_back(sb);

    CompoundBow cb(config);
    cb.set_posX(600);
    cb.set_posY(90);
    cb.set_amount(1);
    world.items.push_back(cb);

    LifePotion life(config);
    life.set_posX(700);
    life.set_posY(90);
    life.set_amount(1);
    world.items.push_back(life);

    ManaPotion mana(config);
    mana.set_posX(800);
    mana.set_posY(90);
    mana.set_amount(1);
    world.items.push_back(mana);
}



