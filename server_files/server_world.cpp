
#include "server_world.h"
#include <iostream>

ServerWorld::ServerWorld() {}

Character* ServerWorld::get(uint16_t message_id) {
    return this->characters[message_id];
}

Attackable* ServerWorld::get_from_position(uint16_t player_id, int16_t other_posX, int16_t other_posY) {
    std::map<uint16_t, Character*>::iterator characters_itr;
    std::map<uint16_t, NPC*>::iterator npc_itr;

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

Attackable* ServerWorld::get_closest_from_position(int16_t npc_posX, int16_t npc_posY) {
    std::map<uint16_t, Character*>::iterator characters_itr;
    for (characters_itr = characters.begin(); characters_itr != characters.end(); ++characters_itr) {
        Character* other_character = characters_itr->second;
        if (other_character->is_attackable(npc_posX, npc_posY)) return other_character;
    }
    return NULL;
}

bool ServerWorld::has_character_close(int16_t npc_posX, int16_t npc_posY) {
    std::map<uint16_t, Character*>::iterator characters_itr;
    for (characters_itr = characters.begin(); characters_itr != characters.end(); ++characters_itr) {
        Character* other_character = characters_itr->second;
        if (other_character->is_attackable(npc_posX, npc_posY)) return true;
    }
    return false;
}

bool ServerWorld::has_banker_close(uint16_t id) {
    Character* player = this->characters[id];
    for (unsigned int i = 0; i < bankers.size(); i++) {
        int16_t posX = bankers[i].get_pos_X();
        int16_t posY = bankers[i].get_pos_Y();
        if (player->can_deposit(posX, posY)) return true;
    }
    return false;
}

bool ServerWorld::empty() {
    return (this->characters.size() == 0);
}

bool ServerWorld::is_full(size_t max_npcs) {
    return (this->npcs.size() == max_npcs);
}

void ServerWorld::move_npcs() {
    if (empty()) return;
    std::map<uint16_t, NPC*>::iterator itr;
    for (itr = npcs.begin(); itr != npcs.end(); ++itr) {
        NPC* current = itr->second;
        int16_t posX = current->get_body_pos_X();
        int16_t posY = current->get_body_pos_Y();
        if (!has_character_close(posX, posY)) {
            current->move_random();
        } else{
            Attackable* closest = get_closest_from_position(posX, posY);
            current->move_to(*closest);
            current->attack(*closest);
        }
    }
}

void ServerWorld::recover_characters() {
    if (empty()) return;
    std::map<uint16_t, Character*>::iterator itr;
    for (itr = characters.begin(); itr != characters.end(); ++itr) { 
        itr->second->recover_life();
        itr->second->recover_mana();
    }
}

void ServerWorld::add(uint16_t id, Character* character) {
    this->characters.insert(std::pair<uint16_t, Character*> (id, character));
}

void ServerWorld::add(uint16_t id, NPC* npc) {
    this->npcs.insert(std::pair<uint16_t, NPC*> (id, npc));
}

void ServerWorld::add(Item& item) {
    this->items.push_back(item);
}


void ServerWorld::player_take_item(uint16_t id) {
    std::cout << "Cantidad de items hasta el momento: " << items.size() << std::endl;
    for (unsigned int i = 0; i < items.size(); ++i) {
        std::cout << "ACA LLEGA" << std::endl;
        if (((std::abs(items[i].get_posX() - characters[id]->get_body_pos_X()) < 30) && 
            (std::abs(items[i].get_posY() - characters[id]->get_body_pos_Y()) < 30))) {
            characters[id]->take_item(items[i]);
            std::cout << "Estas cerca como para agarrar un item" << std::endl;
            this->update_world_items(i);
            break;
        }
    }
    std::cout << "Cantidad de items despues: " << items.size() << std::endl;
}


void ServerWorld::update_world_items(unsigned int &i) {
    std::vector<Item> tmp;
    for (unsigned int j = 0; j < items.size(); ++j) {
        if (j == i) 
            continue;

        tmp.push_back(items[j]);
    }
    items.swap(tmp);
}


void ServerWorld::add(Banker banker) {
    this->bankers.push_back(banker);
}

void ServerWorld::remove_character(uint16_t id) {
    // delete this->characters[id];
    this->characters.erase(id);
}

void ServerWorld::remove_npc(uint16_t id) {
    // delete this->npc[id];
    this->npcs.erase(id);
}

void ServerWorld::move_character_right(uint16_t id) {
    this->characters[id]->move_right();
    if(check_characters_collision(id) || check_npcs_collision(id)) this->characters[id]->move_left();
}

void ServerWorld::move_character_left(uint16_t id) {
    this->characters[id]->move_left();
    if(check_characters_collision(id) || check_npcs_collision(id)) this->characters[id]->move_right();
}

void ServerWorld::move_character_down(uint16_t id) {
    this->characters[id]->move_down();
    if(check_characters_collision(id) || check_npcs_collision(id)) this->characters[id]->move_top();
}

void ServerWorld::move_character_top(uint16_t id) {
    this->characters[id]->move_top();
    if(check_characters_collision(id) || check_npcs_collision(id)) this->characters[id]->move_down();
}

bool ServerWorld::check_characters_collision(uint16_t id) {
    std::map<uint16_t, Character*>::iterator characters_itr;
    Character* me = this->characters[id];

    for (characters_itr = characters.begin(); characters_itr != characters.end(); ++characters_itr) {
        Attackable* other = this->characters[characters_itr->first];
        if (characters_itr->first == id) 
            continue;
        
        if (check_collision(me, other)) return true;
    }
    return false;
}

bool ServerWorld::check_npcs_collision(uint16_t id) {
    std::map<uint16_t, NPC*>::iterator npc_itr;
    Character* me = this->characters[id];

    for (npc_itr = npcs.begin(); npc_itr != npcs.end(); ++npc_itr) { 
        Attackable* other = this->npcs[npc_itr->first];       
        if (check_collision(me, other)) return true;
    }
    return false;
}

bool ServerWorld::check_collision(Attackable* me, Attackable* other) {
    int leftMe = me->get_body_pos_X();
    int rightMe = me->get_body_pos_X() + me->get_width(); // CAMBIAR POR UN GETTER A LA RAZA

    int topMe = me->get_body_pos_Y();
    int bottomMe = me->get_body_pos_Y() + me->get_height(); // CAMBIAR POR UN GETTER A LA RAZA

    int leftOther = other->get_body_pos_X();
    int rightOther = other->get_body_pos_X() + other->get_width(); // CAMBIAR POR UN GETTER A LA RAZA

    int topOther = other->get_body_pos_Y();
    int bottomOther = other->get_body_pos_Y() + other->get_height();; // CAMBIAR POR UN GETTER A LA RAZA

    if( bottomMe <= topOther ) return false;
    
    if( topMe >= bottomOther ) return false;
    if( rightMe <= leftOther ) return false;
    if( leftMe >= rightOther ) return false;

    return true;
}
