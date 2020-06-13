#include <stdint.h>
#include <msgpack.hpp>

#include "../common_protocol_message.h"
#include "server_sender_thread.h"

#define CHARACTER_WIDTH 21
#define CHARACTER_HEIGHT 31

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


ServerSenderThread::ServerSenderThread(
    Socket &skt, 
    Queue &queue) : skt(skt), queue(queue), running(true) {}


void ServerSenderThread::run() {

    while (this->running) {
        ProtocolMessage msg = this->queue.pop();
        this->process_message(msg);

        // std::cout << "MANDANDO: " << std::endl;
        // std::cout << "POS X: " << msg.posX << std::endl;
        // std::cout << "POS Y: " << msg.posY << std::endl;
        // std::cout << "ID: " << msg.id << std::endl;


        msgpack::sbuffer buffer;
        msgpack::packer<msgpack::sbuffer> pk(&buffer);
        pk.pack(msg);
        this->skt(buffer);
    }
}



void ServerSenderThread::process_message(ProtocolMessage &msg) {
    if (msg.id == 1) 
        return this->process_move(msg);
}




void ServerSenderThread::process_move(ProtocolMessage &msg) {
    
	msg.bodyPosX += msg.velX;
    msg.headPosX += msg.velX;
	if( ( msg.bodyPosX < 0 ) || ( msg.bodyPosX + (CHARACTER_WIDTH) > SCREEN_WIDTH ) ) {
		msg.bodyPosX -= msg.velX;
        msg.headPosX -= msg.velX;
    }

	msg.bodyPosY += msg.velY;
    msg.headPosY += msg.velY;
	if( ( msg.headPosY < 0 ) || ( msg.bodyPosY + (CHARACTER_HEIGHT) > SCREEN_HEIGHT ) ) { 
		msg.bodyPosY -= msg.velY;
        msg.headPosY -= msg.velY;
    }

    msg.id = 2;
}

