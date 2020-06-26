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
        // Check ID and process what you have to process
        // Send the updated data
        ProtocolMessage msg = this->queue.pop();
        this->process_message(msg);
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
    
	msg.character.bodyPosX += msg.character.velX;
    msg.character.headPosX += msg.character.velX;
	if( ( msg.character.bodyPosX < 0 ) || ( msg.character.bodyPosX + (CHARACTER_WIDTH) > SCREEN_WIDTH ) ) {
		msg.character.bodyPosX -= msg.character.velX;
        msg.character.headPosX -= msg.character.velX;
    }

	msg.character.bodyPosY += msg.character.velY;
    msg.character.headPosY += msg.character.velY;
	if( ( msg.character.headPosY < 0 ) || ( msg.character.bodyPosY + (CHARACTER_HEIGHT) > SCREEN_HEIGHT ) ) { 
		msg.character.bodyPosY -= msg.character.velY;
        msg.character.headPosY -= msg.character.velY;
    }

    msg.id = 2;
}

