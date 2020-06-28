#include <msgpack.hpp>

#include "client_receiver_thread.h"
#include "client_drawable.h"


ClientReceiverThread::ClientReceiverThread(
    Socket &skt, 
    Player &player,
    SDL_Rect &camera) : skt(skt), 
                        player(player),
                        camera(camera),
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
    if (msg.id == 20)
        this->process_move(msg);
    if (msg.id == 30)
        this->process_equip_helmet(msg);
    if (msg.id == 31)
        this->process_equip_armor(msg);

    this->player.set_camera(camera);
}


void ClientReceiverThread::process_move(ProtocolMessage &msg) {
    this->player.set_position((int) msg.character.bodyPosX, (int) msg.character.bodyPosY, (int) msg.character.headPosX, (int) msg.character.headPosY);
}

void ClientReceiverThread::process_equip_helmet(ProtocolMessage &msg) {
    this->player.set_helmet(msg.character.helmetId);
}

void ClientReceiverThread::process_equip_armor(ProtocolMessage &msg) {
    this->player.set_armor(msg.character.armorId);
}
