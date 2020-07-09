#include <stdint.h>
#include <msgpack.hpp>

#include "../common_files/common_protocol_message.h"
#include "server_game_loop_thread.h"

#define MILISECONDS_TO_CREATE 3000
#define MILISECONDS_TO_UPDATE 2000
#define NPC_STARTING_ID 100
#define NPC_CREATION_MSG_ID 70
#define NPC_UPDATE_MSG 72
#define MAX_NPC_TYPES 4

GameLoopThread::GameLoopThread(
    Queue &queue, 
    int max_npcs) : queue(queue), running(true), max_npcs(max_npcs) {}



void GameLoopThread::run() {

    std::cout << "GameLoopThread Running::" << std::endl;
    create_npcs();
    int iteration = 1;
    while (this->running) {
        std::cout << "Me voy a dormir 2 Secs" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(MILISECONDS_TO_UPDATE));
        // if (iteration % 2 == 0) {
            // Updatea vida y mana 1 vez por segundo
            // update_characters();
        // }
        std::cout << "Sendeo el Update" << std::endl;
        ProtocolMessage update_msg(NPC_UPDATE_MSG);
        queue.push(update_msg);
        iteration++;
    }
}

void GameLoopThread::create_npcs() {
    int npc_id = NPC_STARTING_ID;
    int npc_type = 1;
    for (int i = 0; i < max_npcs; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(MILISECONDS_TO_CREATE));
        std::cout << "Creating NPCs::" << std::endl;
        ProtocolNpc npc(npc_id, npc_type);
        ProtocolMessage npc_msg(NPC_CREATION_MSG_ID, npc_id, std::move(npc));
        queue.push(npc_msg);
        npc_id++;
        npc_type++;
        if(npc_type > MAX_NPC_TYPES) npc_type = 1;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(MILISECONDS_TO_CREATE));
}