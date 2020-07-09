
#include "server_world.h"
#include <iostream>

ServerWorld::ServerWorld() {}


Character* ServerWorld::get(int16_t message_id) {
    return this->characters[message_id];
}

Attackable* ServerWorld::get_from_position(int player_id, int other_posX, int other_posY) {
    std::map<int16_t, Character*>::iterator characters_itr;
    std::map<int16_t, NPC*>::iterator npc_itr;

    for (characters_itr = characters.begin(); characters_itr != characters.end(); ++characters_itr) {
        if (characters_itr->first == player_id) continue;
        Character* other_character = characters_itr->second;
        if (other_character->is_near(other_posX, other_posY)) return other_character;
    }

    for (npc_itr = npcs.begin(); npc_itr != npcs.end(); ++npc_itr) {
        if (npc_itr->first == player_id) continue;
        NPC* other_npc = npc_itr->second;
        if (other_npc->is_near(other_posX, other_posY)) return other_npc;
    }
    return NULL;
}

bool ServerWorld::empty() {
    return (this->characters.size() == 0);
}

void ServerWorld::add(int16_t id, Character* character) {
    this->characters.insert(std::pair<int16_t, Character*> (id, character));
}

void ServerWorld::add(int16_t id, NPC* npc) {
    this->npcs.insert(std::pair<int16_t, NPC*> (id, npc));
}

