#include <msgpack.hpp>

#include "client_receiver_thread.h"
#include "client_drawable.h"


ClientReceiverThread::ClientReceiverThread(
    Socket &skt, 
    ClientWorld &world,
    SDL_Rect &camera,
    uint16_t player_id) : skt(skt), 
                        world(world),
                        camera(camera),
                        player_id(player_id),
                        running(true) {}



void ClientReceiverThread::run() {

    while (this->running) {
        ProtocolMessage msg;
        msgpack::unpacker pac;
        std::cout << "Corriendo" << std::endl;
        this->skt >> pac;
        msgpack::object_handle oh;
        pac.next(oh);
        msgpack::object obj = oh.get();
        obj.convert(msg);
        this->process_response(msg);
    }
}


void ClientReceiverThread::process_response(ProtocolMessage &msg) {
    if (msg.id_message == 20)
        this->process_move(msg);
    if (msg.id_message == 30)
        this->process_equip_helmet(msg);
    if (msg.id_message == 31)
        this->process_equip_armor(msg);
    if (msg.id_message == 32)
        this->process_equip_weapon(msg);
    if (msg.id_message == 66)
        this->process_create_player(msg);

    world.players[this->player_id]->set_camera(camera);
}


void ClientReceiverThread::process_move(ProtocolMessage &msg) {
    Player* player = world.players[msg.id_player];
    player->set_position((int) msg.characters[0].bodyPosX, (int) msg.characters[0].bodyPosY);
}

void ClientReceiverThread::process_equip_helmet(ProtocolMessage &msg) {
    Player* player = world.players[msg.id_player];
    player->set_helmet(msg.characters[0].helmetId);
}

void ClientReceiverThread::process_equip_armor(ProtocolMessage &msg) {
    Player* player = world.players[msg.id_player];
    player->set_armor(msg.characters[0].armorId);
}

void ClientReceiverThread::process_equip_weapon(ProtocolMessage &msg) {
    Player* player = world.players[msg.id_player];
    player->set_weapon(msg.characters[0].weaponId);
}

void ClientReceiverThread::process_create_player(ProtocolMessage &msg) {
    int i = msg.find(msg.id_player);
    if (i != -1)
        world.add_player(msg.characters[i]);
}