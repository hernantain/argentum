#include <msgpack.hpp>

#include "client_receiver_thread.h"
#include "client_drawable.h"


ClientReceiverThread::ClientReceiverThread(
    Socket &skt, 
    ClientWorld &world,
    SDL_Rect &camera,
    InfoView &infoView,
    uint16_t player_id) : skt(skt), 
                        world(world),
                        camera(camera),
                        infoView(infoView),
                        player_id(player_id),
                        running(true) {}



void ClientReceiverThread::run() {
    while (this->running) {
        ProtocolMessage msg;
        msgpack::unpacker pac;
        this->skt >> pac;
        msgpack::object_handle oh;
        pac.next(oh);
        msgpack::object obj = oh.get();
        obj.convert(msg);
        this->process_response(msg);
    }
}


void ClientReceiverThread::process_response(ProtocolMessage &msg) {
    // std::cout << "PROCESANDO RESPUESTA: " << msg.id_message << std::endl;
    if (msg.id_message == 20)
        this->process_move(msg);
    if (msg.id_message == 25)
        // here we might put a sound on attacks 
        this->process_attack(msg);
    if (msg.id_message == 30)
        this->process_equip_helmet(msg);
    if (msg.id_message == 31)
        this->process_equip_armor(msg);
    if (msg.id_message == 32)
        this->process_equip_weapon(msg);
    if (msg.id_message == 34)
        this->process_meditation(msg);
    if (msg.id_message == 66)
        this->process_create_player(msg);
    if (msg.id_message == 71)
        this->process_create_npc(msg);
    
    if (msg.id_player == this->player_id)
        world.players[this->player_id]->set_camera(camera);
}


void ClientReceiverThread::process_move(ProtocolMessage &msg) {
    Player* player = world.players[msg.id_player];
    int i = msg.find(msg.id_player);

    player->set_position((int) msg.characters[i].bodyPosX, (int) msg.characters[i].bodyPosY, (int) msg.characters[i].orientation);
}

void ClientReceiverThread::process_equip_helmet(ProtocolMessage &msg) {
    Player* player = world.players[msg.id_player];
    int i = msg.find(msg.id_player);
    player->set_helmet(msg.characters[i].helmetId);
}

void ClientReceiverThread::process_equip_armor(ProtocolMessage &msg) {
    Player* player = world.players[msg.id_player];
    int i = msg.find(msg.id_player);
    player->set_armor(msg.characters[i].armorId);
}

void ClientReceiverThread::process_equip_weapon(ProtocolMessage &msg) {
    Player* player = world.players[msg.id_player];
    player->set_weapon(msg.characters[0].weaponId);
}


void ClientReceiverThread::process_meditation(ProtocolMessage &msg) {
    // Player* player = world.players[msg.id_player];
    // std::cout << "Estoy meditando" << std::endl;
    // player->set_meditation();
}


void ClientReceiverThread::process_create_player(ProtocolMessage &msg) {

    // for (unsigned int i = 0; i < msg.characters.size(); ++i)
    //     std::cout << msg.characters[i].id << std::endl;

    int i = msg.find(msg.id_player);
    if (i != -1)
        world.add_player(msg.characters[i]);
}


void ClientReceiverThread::process_create_npc(ProtocolMessage &msg) {

    for (unsigned int i = 0; i < msg.npcs.size(); ++i)
        std::cout << msg.npcs[i].id << std::endl;

    int i = msg.find_npc(msg.id_player);
    if (i != -1)
        world.add_npc(msg.npcs[i]);
}



void ClientReceiverThread::process_attack(ProtocolMessage &msg) {
    int i = msg.find(this->player_id);
    if (i != -1) {
        this->infoView.set_life(msg.characters[i].life, msg.characters[i].max_life);
        this->infoView.set_mana(msg.characters[i].mana, msg.characters[i].max_mana);
    }

}
