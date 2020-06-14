#include <msgpack.hpp>

#include "client_receiver_thread.h"
#include "client_drawable.h"


ClientReceiverThread::ClientReceiverThread(
    Socket &skt, 
    Player &player) : skt(skt), 
                        player(player),
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
    if (msg.id == 2)
        this->process_move(msg);
}


void ClientReceiverThread::process_move(ProtocolMessage &msg) {
    this->player.set_position((int) msg.bodyPosX, (int) msg.bodyPosY, (int) msg.headPosX, (int) msg.headPosY);
}
