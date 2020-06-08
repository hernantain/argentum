#include <stdint.h>
#include <msgpack.hpp>

#include "common_protocol_message.h"
#include "server_sender_thread.h"

#define CHARACTER_WIDTH 21
#define CHARACTER_HEIGHT 31

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


ServerSenderThread::ServerSenderThread(
    Socket &skt, 
    Queue &queue) : skt(skt), queue(queue) {}



void ServerSenderThread::run() {

    bool running = true;

    while (running) {
        ProtocolMessage msg = this->queue.pop();
        this->process_message(msg);

        std::cout << "MANDANDO: " << std::endl;
        std::cout << "POS X: " << msg.posX << std::endl;
        std::cout << "POS Y: " << msg.posY << std::endl;
        std::cout << "ID: " << msg.id << std::endl;


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
    

	msg.posX += msg.velX;
	if( ( msg.posX < 0 ) || ( msg.posX + (CHARACTER_WIDTH) > SCREEN_WIDTH ) )
		msg.posX -= msg.velX;

	msg.posY += msg.velY;
	if( ( msg.posY < 0 ) || ( msg.posY + (CHARACTER_HEIGHT) > SCREEN_HEIGHT ) ) 
		msg.posY -= msg.velY;

    msg.id = 2;
}

