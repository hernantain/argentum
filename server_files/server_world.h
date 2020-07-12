#ifndef _SERVER_WORLD
#define _SERVER_WORLD

#include <map>
#include <stdint.h>
#include "server_character.h"
#include "server_npc.h"
#include "server_item.h"
#include "server_banker.h"
#include "server_attackable.h"

struct ServerWorld {

    std::map<uint16_t, Character*> characters;
    std::map<uint16_t, NPC*> npcs;
    std::vector<Item> items;
    std::vector<Banker> bankers;

    ServerWorld();

    Character* get(uint16_t message_id);
    Attackable* get_closest_from_position(int16_t npc_posX, int16_t npc_posY);
    Attackable* get_from_position(uint16_t player_id, int16_t posX, int16_t posY);

    bool has_banker_close(uint16_t id);
    bool has_character_close(int16_t npc_posX, int16_t npc_posY);
    void move_npcs();
    void recover_characters();
    
    bool empty();
    bool is_full(size_t max_npcs);

    void add(uint16_t id, Character* character);
    void add(uint16_t id, NPC* npc);
    void add(Item& item);
    void add(Banker banker);

    void move_character_right(uint16_t id);
    void move_character_left(uint16_t id);
    void move_character_down(uint16_t id);
    void move_character_top(uint16_t id);

    void player_take_item(uint16_t id);
    void update_world_items(unsigned int &i);

    bool check_characters_collision(uint16_t id);
    bool check_npcs_collision(uint16_t id);

    bool check_collision(Attackable* me, Attackable* other);

    void remove_npc(uint16_t id);
    void remove_character(uint16_t id);

};



#endif
