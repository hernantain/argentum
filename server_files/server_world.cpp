
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

bool ServerWorld::has_priest_close(uint16_t id) {
    Character* player = this->characters[id];
    for (unsigned int i = 0; i < priests.size(); i++) {
        int16_t posX = priests[i].get_pos_X();
        int16_t posY = priests[i].get_pos_Y();
        if (player->can_resurrect(posX, posY)) {
            return true;
        }
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
        if(itr->second->is_meditating()) {
            itr->second->meditate();
            std::cout << "Estoy meditando" << std::endl;
            continue;
        }
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

void ServerWorld::add(Banker banker) {
    this->bankers.push_back(banker);
}

void ServerWorld::add(Priest priest) {
    this->priests.push_back(priest);
}


void ServerWorld::player_take_item(uint16_t id) {
    std::cout << "Cantidad de items hasta el momento: " << items.size() << std::endl;
    Character* current = characters[id];
    for (unsigned int i = 0; i < items.size(); ++i) {
        std::cout << "ACA LLEGA" << std::endl;
        int16_t item_posX = items[i].get_posX();
        int16_t item_posY = items[i].get_posY();
        if ((current->is_near(item_posX, item_posY)) && (this->characters[id]->is_alive())) {
            characters[id]->take_item(items[i]);
            // std::cout << "Estas cerca como para agarrar un item" << std::endl;
            this->update_world_items(i);
            break;
        }
    }
    // std::cout << "Cantidad de items despues: " << items.size() << std::endl;
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
    std::map<uint16_t, Character*>::iterator characters_itr;
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


void ServerWorld::move_character_left(uint16_t id) {
    this->characters[id]->move_left();
    std::map<uint16_t, Character*>::iterator characters_itr;
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


void ServerWorld::move_character_down(uint16_t id) {
    this->characters[id]->move_down();
    std::map<uint16_t, Character*>::iterator characters_itr;
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


void ServerWorld::move_character_top(uint16_t id) {
    this->characters[id]->move_top();
    std::map<uint16_t, Character*>::iterator characters_itr;
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



bool ServerWorld::check_collision(uint16_t id, uint16_t other_id) {
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

    if( bottomMe <= topOther ) return false;
    if( topMe >= bottomOther ) return false;
    if( rightMe <= leftOther ) return false;
    if( leftMe >= rightOther ) return false;

    return true;
}
