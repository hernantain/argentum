#ifndef _SERVER_WORLD
#define _SERVER_WORLD

#include <map>
#include <stdint.h>
#include "server_character.h"
#include "server_npc.h"
#include "server_item.h"
#include "server_attackable.h"

struct ServerWorld {

    std::map<int16_t, Character*> characters;
    std::map<int16_t, NPC*> npcs;
    std::vector<Item*> items;

    ServerWorld();

    Character* get(int16_t message_id);

    Attackable* get_from_position(int player_id, int posX, int posY);
    int get_id_from_position(int player_id, int posX, int posY);

    int dead_npcs();
    void move_npcs();
    void recover_characters();
    
    bool empty();

    void add(int16_t id, Character* character);
    void add(int16_t id, NPC* npc);
    void add(Item* item);

    void move_character_right(int16_t id);
    void move_character_left(int16_t id);
    void move_character_down(int16_t id);
    void move_character_top(int16_t id);

    bool check_collision(int16_t id, int16_t other_id);

    void remove_character(int16_t id);
    void remove_npc(int16_t id);

};



#endif
