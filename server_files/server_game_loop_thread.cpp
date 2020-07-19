#include <stdint.h>
#include <msgpack.hpp>

#include "../common_files/common_protocol_message.h"
#include "../common_files/common_protocol_codes.h"

#include "server_game_loop_thread.h"

#define MILISECONDS_TO_CREATE 3000
#define MILISECONDS_TO_UPDATE 1000

#define NPC_INITIAL_ID 100
#define NPC_INITIAL_TYPE 1
#define MAX_NPC_TYPES 4


#include <vector>


GameLoopThread::GameLoopThread(MessageToServerQueue &queue) : queue(queue), running(true) {}


void GameLoopThread::run() {
    std::cout << "GameLoopThread Running::" << std::endl;
    uint16_t npc_id = NPC_INITIAL_ID;
    int16_t npc_type = NPC_INITIAL_TYPE;
    int iteration = 1;
    while (this->running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(MILISECONDS_TO_UPDATE));
        if (iteration % 2 == 0) {
            // Every 2 seconds

            std::vector<int16_t> args;
            MessageToServer message(
                PROTOCOL_UPDATE_NPCS,
                -1, 
                args
            );
            queue.push(message);
        }
        if (iteration % 3 == 0) {
            // Every 3 seconds

            std::vector<int16_t> args;
            args.push_back(npc_type);
            MessageToServer message(
                PROTOCOL_CREATE_NPC,
                npc_id, 
                args
            );
            queue.push(message);
        }
        // Every second
        
        std::vector<int16_t> args;
        args.push_back(npc_type);
        MessageToServer message(
            PROTOCOL_UPDATE_CHARACTERS,
            -1, 
            args
        );
        queue.push(message);

        iteration++;
        npc_id++;
        npc_type++;
        if(npc_type > MAX_NPC_TYPES) npc_type = NPC_INITIAL_TYPE;
    }
}
