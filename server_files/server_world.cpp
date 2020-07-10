
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
        NPC* other_npc = npc_itr->second;
        if (other_npc->is_near(other_posX, other_posY)) return other_npc;
    }
    return NULL;
}

bool ServerWorld::empty() {
    return (this->characters.size() == 0);
}

int ServerWorld::dead_npcs() {
    if (empty()) return;
    int deaths = 0;
    std::map<int16_t, NPC*>::iterator itr;
    for (itr = npcs.begin(); itr != npcs.end(); ++itr) {
        if(!itr->second->is_alive()) deaths++;
    }
    return deaths;
}

void ServerWorld::move_npcs() {
    if (empty()) return;
    std::map<int16_t, NPC*>::iterator itr;
    for (itr = npcs.begin(); itr != npcs.end(); ++itr) {
        itr->second->move_random();
    }
}

void ServerWorld::recover_characters() {
    if (empty()) return;
    std::map<int16_t, Character*>::iterator itr;
    for (itr = characters.begin(); itr != characters.end(); ++itr) { 
        itr->second->recover_life();
        itr->second->recover_mana();
    }
}

void ServerWorld::add(int16_t id, Character* character) {
    this->characters.insert(std::pair<int16_t, Character*> (id, character));
}

void ServerWorld::add(int16_t id, NPC* npc) {
    this->npcs.insert(std::pair<int16_t, NPC*> (id, npc));
}

void ServerWorld::add(Item* item) {
    this->items.push_back(item);
}

void ServerWorld::remove_character(int16_t id) {
    // delete this->characters[id];
    this->characters.erase(id);
}

void ServerWorld::remove_npc(int16_t id) {
    this->npcs.erase(id);
}

void ServerWorld::move_character_right(int16_t id) {
    this->characters[id]->move_right();
    std::map<int16_t, Character*>::iterator characters_itr;
    // std::map<int16_t, NPC*>::iterator npc_itr;

    for (characters_itr = characters.begin(); characters_itr != characters.end(); ++characters_itr) {
        if (characters_itr->first == id) 
            continue;
        
        if (check_collision(id, characters_itr->first)) {
            this->characters[id]->move_left();
            break;
        }
    }
}


void ServerWorld::move_character_left(int16_t id) {
    this->characters[id]->move_left();
    std::map<int16_t, Character*>::iterator characters_itr;
    // std::map<int16_t, NPC*>::iterator npc_itr;

    for (characters_itr = characters.begin(); characters_itr != characters.end(); ++characters_itr) {
        if (characters_itr->first == id) 
            continue;
        
        if (check_collision(id, characters_itr->first)) {
            this->characters[id]->move_right();
            break;
        }
    }
}


void ServerWorld::move_character_down(int16_t id) {
    this->characters[id]->move_down();
    std::map<int16_t, Character*>::iterator characters_itr;
    // std::map<int16_t, NPC*>::iterator npc_itr;

    for (characters_itr = characters.begin(); characters_itr != characters.end(); ++characters_itr) {
        if (characters_itr->first == id) 
            continue;
        
        if (check_collision(id, characters_itr->first)) {
            this->characters[id]->move_top();
            break;
        }
    }
}


void ServerWorld::move_character_top(int16_t id) {
    this->characters[id]->move_top();
    std::map<int16_t, Character*>::iterator characters_itr;
    // std::map<int16_t, NPC*>::iterator npc_itr;

    for (characters_itr = characters.begin(); characters_itr != characters.end(); ++characters_itr) {
        if (characters_itr->first == id) 
            continue;
        
        if (check_collision(id, characters_itr->first)) {
            this->characters[id]->move_down();
            break;
        }
    }
}



bool ServerWorld::check_collision(int16_t id, int16_t other_id) {
    Character* me = this->characters[id];
    Character* other = this->characters[other_id];

    int leftMe = me->get_body_pos_X();
    int rightMe = me->get_body_pos_X() + 21; // CAMBIAR POR UN GETTER A LA RAZA
    int topMe = me->get_body_pos_Y();
    int bottomMe = me->get_body_pos_Y() + 31; // CAMBIAR POR UN GETTER A LA RAZA

    int leftOther = other->get_body_pos_X();
    int rightOther = other->get_body_pos_X() + 21; // CAMBIAR POR UN GETTER A LA RAZA
    int topOther = other->get_body_pos_Y();
    int bottomOther = other->get_body_pos_Y() + 31; // CAMBIAR POR UN GETTER A LA RAZA

    if( bottomMe <= topOther )
        return false;

    if( topMe >= bottomOther )
        return false;

    if( rightMe <= leftOther )
        return false;

    if( leftMe >= rightOther )
        return false;

    return true;
}
