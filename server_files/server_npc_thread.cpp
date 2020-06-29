#include <stdint.h>
#include <msgpack.hpp>

#include "../common_protocol_message.h"
#include "server_npc_thread.h"

#define SECONDS_TO_UPDATE 2

ServerNPCThread::ServerNPCThread(Socket &skt, Queue &queue, int max_npcs) : 
    skt(skt), queue(queue), running(true), max_npcs(max_npcs) {}

void ServerNPCThread::run() {

    while (this->running) {
        std::cout << "Sleeping" << std::endl;
        sleep(SECONDS_TO_UPDATE);
        std::cout << "Updating" << std::endl;
        // ProtocolMessage updated_npc_msg = update_npcs();
        // queue.push(updated_npc_msg);
    }
}

// ProtocolMessage ServerNPCThread::update_npcs() {
    // I should have the world as an attribute of this class
    // In particular im interested on the NPCs vector
    // For each NPC on the world I will send probably
    // PosX, PosY, Id --> to identify the type.
    // Also I should check if the NPC is alive or not ?
    // And lastly I should check at every iteration
    // if the number of NPCs is <= to "max_npcs"
    // If its not, i can make a randint (1,4)
    // To choose which NPC i should create
// }
