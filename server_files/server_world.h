#ifndef _SERVER_WORLD
#define _SERVER_WORLD

#include <map>
#include <stdint.h>
#include "server_character.h"


struct ServerWorld {

    std::map<int16_t, Character*> characters;
    // NPCs
    // Items

    ServerWorld();

    Character* get(int16_t message_id);

    Character* get_from_position(int player_id, int posX, int posY);

    bool empty();

    void add(int16_t id, Character* character);
        

};



#endif
