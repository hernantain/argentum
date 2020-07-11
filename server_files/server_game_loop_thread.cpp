#include <stdint.h>
#include <msgpack.hpp>

#include "../common_files/common_protocol_message.h"
#include "server_game_loop_thread.h"

#define MILISECONDS_TO_CREATE 3000
#define MILISECONDS_TO_UPDATE 1000

#define NPC_INITIAL_ID 100
#define NPC_INITIAL_TYPE 1
#define MAX_NPC_TYPES 4

#define NPC_CREATION_MSG_ID 70
#define NPC_UPDATE_MSG 72
#define CHARACTERS_UPDATE_MSG 74

GameLoopThread::GameLoopThread(Queue &queue) : queue(queue), running(true) {}


void GameLoopThread::run() {

    std::cout << "GameLoopThread Running::" << std::endl;
    uint16_t npc_id = NPC_INITIAL_ID;
    int16_t npc_type = NPC_INITIAL_TYPE;
    int iteration = 1;
    while (this->running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(MILISECONDS_TO_UPDATE));
        if (iteration % 2 == 0) {
            // Every 2 seconds
            ProtocolMessage npcs_update_msg(NPC_UPDATE_MSG);
            queue.push(npcs_update_msg);
        }
        if (iteration % 3 == 0) {
            // Every 3 seconds
            ProtocolNpc npc(npc_id, npc_type);
            ProtocolMessage npc_create_msg(NPC_CREATION_MSG_ID, npc_id, std::move(npc));
            queue.push(npc_create_msg);
        }
        // Every second
        ProtocolMessage characters_update_msg(CHARACTERS_UPDATE_MSG);
        queue.push(characters_update_msg);
        iteration++;
        npc_id++;
        npc_type++;
        if(npc_type > MAX_NPC_TYPES) npc_type = NPC_INITIAL_TYPE;
    }
}
