
#include "server_world.h"
#include <iostream>

ServerWorld::ServerWorld() {}


Character* ServerWorld::get(int16_t message_id) {
    return this->characters[message_id];
}

Character* ServerWorld::get_from_position(int player_id, int other_posX, int other_posY) {
    std::map<int16_t, Character*>::iterator itr;

    for (itr = characters.begin(); itr != characters.end(); ++itr) {
        if (itr->first == player_id) continue;
        Character* other = itr->second;
        if (other->is_near(other_posX, other_posY)) return other;
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


void ServerWorld::remove_character(int16_t id) {
    delete this->characters[id];
    this->characters.erase(id);
}
