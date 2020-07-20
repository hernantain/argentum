#include <stdint.h>
#include <msgpack.hpp>
#include <vector>

#include "../common_files/common_protocol_message.h"
#include "../common_files/common_protocol_codes.h"

#include "server_game_loop_thread.h"

#define UPDATE_RATE 1000

#define NPC_INITIAL_ID 100
#define NPC_INITIAL_TYPE 1
#define MAX_NPC_TYPES 4
#define NPC_CREATION_ITERATION 3


GameLoopThread::GameLoopThread(MessageToServerQueue &queue) : queue(queue), running(true) {}


void GameLoopThread::run() {
    std::cout << "GameLoopThread Running::" << std::endl;
    using namespace std::chrono;
    uint16_t npc_id = NPC_INITIAL_ID;
    int16_t npc_type = NPC_INITIAL_TYPE;

    int iteration = 0;	
	duration<int, std::milli> rate(UPDATE_RATE);
	system_clock::time_point initial = system_clock::now();

    while (this->running) {
        update_game(iteration, npc_id, npc_type);

        if(iteration % NPC_CREATION_ITERATION == 0) {
            npc_id++;
            npc_type++;
            if(npc_type > MAX_NPC_TYPES) npc_type = NPC_INITIAL_TYPE;
        };

        system_clock::time_point final = system_clock::now();
		duration<int,std::milli> rest = rate - duration_cast<std::chrono::duration<int,std::milli>>(final - initial);
        if (rest.count() < 0) {
			duration<int, std::milli> behind = duration<int, std::milli>(-rest);
			rest = rate - (behind % rate);
			duration<int, std::milli> lost = behind + rest;
			initial += lost;
		 	iteration += (int) floor(lost.count() / rate.count());
		}
        std::this_thread::sleep_for(duration<int, std::milli>(rest.count()));
		initial += rate;
		iteration++;
    }
}

void GameLoopThread::update_game(int iteration, uint16_t npc_id, int16_t npc_type) {
    // Every 3 seconds
    if (iteration % NPC_CREATION_ITERATION == 0) {
        std::vector<int16_t> args;
        args.push_back(npc_type);
        MessageToServer npc_creation(PROTOCOL_CREATE_NPC, npc_id, args);
        queue.push(npc_creation);
    }
    // Every second
    std::vector<int16_t> npc_args{ 0 };
    MessageToServer npc_update(PROTOCOL_UPDATE_NPCS, -1, npc_args);
    queue.push(npc_update);
    // Every second
    std::vector<int16_t> character_args{ 0 };
    MessageToServer characters_update(PROTOCOL_UPDATE_CHARACTERS, -1, character_args);
    queue.push(characters_update);
}
