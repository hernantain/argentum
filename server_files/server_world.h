#ifndef _SERVER_WORLD
#define _SERVER_WORLD

#include <map>
#include <stdint.h>
#include "server_character.h"
#include "server_npc.h"
#include "server_attackable.h"

struct ServerWorld {

    std::map<uint16_t, Character*> characters;
    std::map<uint16_t, NPC*> npcs;
    // Items

    ServerWorld();

    Character* get(uint16_t message_id);

    Attackable* get_from_position(uint16_t player_id, int16_t posX, int16_t posY);

    void move_npcs();
    void recover_characters();
    
    bool empty();

    void add(uint16_t id, Character* character);
    void add(uint16_t id, NPC* npc);

    void move_character_right(uint16_t id);
    void move_character_left(uint16_t id);
    void move_character_down(uint16_t id);
    void move_character_top(uint16_t id);

    bool check_collision(uint16_t id, uint16_t other_id);

    void remove_character(uint16_t id);

};



#endif
