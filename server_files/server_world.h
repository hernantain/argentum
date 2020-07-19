#ifndef _SERVER_WORLD
#define _SERVER_WORLD

#include <map>
#include <stdint.h>
#include "server_character.h"
#include "server_npc.h"
#include "server_item.h"
#include "server_banker.h"
#include "server_priest.h"
#include "server_attackable.h"

struct ServerWorld {

    std::map<uint16_t, Character*> characters;
    std::map<uint16_t, NPC*> npcs;
    std::vector<Item> items;
    std::vector<Banker> bankers;
    std::vector<Priest> priests;

    ServerWorld();

    Character* get(uint16_t message_id);
    Attackable* get_closest_from_position(int16_t npc_posX, int16_t npc_posY);
    Attackable* get_from_position(uint16_t player_id, int16_t posX, int16_t posY);

    bool has_priest_close(const uint16_t id);
    bool has_banker_close(const uint16_t id);
    bool has_character_close(const int16_t npc_posX, const int16_t npc_posY);

    void move_npcs();
    void recover_characters();
    
    bool empty() const;
    bool is_full(const size_t max_npcs) const;

    void add(const uint16_t id, Character* character);
    void add(const uint16_t id, NPC* npc);
    void add(Item& item);
    void add(Banker banker);
    void add(Priest banker);

    void move_character_right(const uint16_t id);
    void move_character_left(const uint16_t id);
    void move_character_down(const uint16_t id);
    void move_character_top(const uint16_t id);

    bool player_take_item(const uint16_t id);
    void update_world_items(unsigned int &i);

    bool check_characters_collision(const uint16_t id);
    bool check_npcs_collision(const uint16_t id);

    bool check_collision(Attackable* me, Attackable* other) const;

    void remove_npc(uint16_t id);
    void remove_character(uint16_t id);

};



#endif
