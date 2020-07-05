#ifndef _SERVER_WORLD
#define _SERVER_WORLD

#include <map>
#include <stdint.h>
#include "server_character.h"
#include "server_npc.h"


struct ServerWorld {

    std::map<int16_t, Character*> characters;
    std::map<int16_t, NPC*> npcs;
    // Items

    ServerWorld();

    Character* get(int16_t message_id);

    bool empty();

    void add(int16_t id, Character* character);
    void add(int16_t id, NPC* npc);

};



#endif
