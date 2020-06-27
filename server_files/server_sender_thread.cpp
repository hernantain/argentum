#include <stdint.h>
#include <msgpack.hpp>

#include "../common_protocol_message.h"
#include "server_sender_thread.h"

ServerSenderThread::ServerSenderThread(
    Socket &skt, 
    Queue &queue) : skt(skt), queue(queue), running(true) {}


void ServerSenderThread::run() {

    while (this->running) {
        // Check ID and process what you have to process
        // Send the updated data
        ProtocolMessage msg = this->queue.pop();
        // this->process_message(msg);
        msgpack::sbuffer buffer;
        msgpack::packer<msgpack::sbuffer> pk(&buffer);
        pk.pack(msg);
        this->skt(buffer);
    }
}
