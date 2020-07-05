#include <stdint.h>
#include <msgpack.hpp>

#include "../common_protocol_message.h"
#include "server_npc_thread.h"

#define SECONDS_TO_UPDATE 2

ServerNPCThread::ServerNPCThread(
    Queue &queue, 
    int max_npcs) : queue(queue), running(true), max_npcs(max_npcs) {}



void ServerNPCThread::run() {

    std::cout << "NPC THREAD CORRIENDO" << std::endl;
    int npc_id = 100;
    int npc_type = 1;
    while (this->running) {
        if (npc_id <= 104) {
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            ProtocolNpc npc(npc_id, npc_type);
            ProtocolMessage npc_msg(70, npc_id, std::move(npc));
            queue.push(npc_msg);
            npc_id++;
            npc_type++;
        }
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
