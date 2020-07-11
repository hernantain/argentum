
#include <iostream>

#include "client_player.h"
#include "client_elf.h"
#include "client_human.h"
#include "client_dwarf.h"
#include "client_gnome.h"
#include "client_world.h"



ClientWorld::ClientWorld(SDL_Renderer *gRenderer) {
    this->gRenderer = gRenderer;
}
    

void ClientWorld::add_player(uint16_t id, Player* player) {
    std::cout << "Antes de insertar, tamanio: " << players.size() << std::endl;
    std::cout << "Insertando " << id << std::endl;
    this->players.insert(std::pair<uint16_t, Player*> (id, player));
    std::cout << "Despues de insertar, tamanio: " << players.size() << std::endl;
}

void ClientWorld::add_npc(uint16_t id, NPC* npc) {
    // std::cout << "Insertando " << id << std::endl;
    this->npcs.insert(std::pair<uint16_t, NPC*> (id, npc));
}


Player* ClientWorld::get_player(uint16_t id) {
    std::unique_lock<std::mutex> lock(m);
    return this->players[id];
}


void ClientWorld::add_player(ProtocolCharacter &protocolCharacter) {
    std::unique_lock<std::mutex> lock(m);
    Player* player;
    std::cout << "PROTOCOL_CHARACTER ID: " << protocolCharacter.id << std::endl;
    if (protocolCharacter.id_race == 1) {
        player = new Human(gRenderer, protocolCharacter.id, protocolCharacter.bodyPosX, protocolCharacter.bodyPosY);
        this->add_player(protocolCharacter.id, player);
    
    } else if (protocolCharacter.id_race == 2) {
        player = new Elf(gRenderer, protocolCharacter.id, protocolCharacter.bodyPosX, protocolCharacter.bodyPosY);
        this->add_player(protocolCharacter.id, player);
    
    } else if (protocolCharacter.id_race == 3) {
        player = new Dwarf(gRenderer, protocolCharacter.id, protocolCharacter.bodyPosX, protocolCharacter.bodyPosY);
        this->add_player(protocolCharacter.id, player);

    } else {
        player = new Gnome(gRenderer, protocolCharacter.id, protocolCharacter.bodyPosX, protocolCharacter.bodyPosY);
        this->add_player(protocolCharacter.id, player);
    }

}


void ClientWorld::add_npc(ProtocolNpc &protocolNpc) {
    std::unique_lock<std::mutex> lock(m);
    NPC* npc = new NPC(protocolNpc.id, protocolNpc.npc_type, gRenderer, protocolNpc.posX, protocolNpc.posY);
    this->add_npc(protocolNpc.id, npc);
}

void ClientWorld::update_npcs(ProtocolMessage &msg) {
    std::unique_lock<std::mutex> lock(m);
    for (unsigned int i = 0; i < msg.npcs.size(); ++i) {
        int16_t npc_id = msg.npcs[i].id;
        NPC* npc = npcs[npc_id];
        npc->set_position((int) msg.npcs[i].posX, (int) msg.npcs[i].posY, (int) msg.npcs[i].orientation);
    }
}


void ClientWorld::move_player(uint16_t id, int16_t newPosX, int16_t newPosY, int16_t orientation) {
    std::unique_lock<std::mutex> lock(m);
    Player* player = players[id];
    player->set_position(newPosX, newPosY, orientation);
}


void ClientWorld::player_set_helmet(uint16_t id, uint8_t helmet_id) {
    std::unique_lock<std::mutex> lock(m);
    Player* player = players[id];
    player->set_helmet(helmet_id);
}

void ClientWorld::player_set_armor(uint16_t id, uint8_t armor_id) {
    std::unique_lock<std::mutex> lock(m);
    Player* player = players[id];
    player->set_armor(armor_id);
}

void ClientWorld::player_set_weapon(uint16_t id, uint8_t weapon_id) {
    std::unique_lock<std::mutex> lock(m);
    Player* player = players[id];
    player->set_weapon(weapon_id);
}

void ClientWorld::player_set_shield(uint16_t id, uint8_t shield_id) {
    std::unique_lock<std::mutex> lock(m);
    Player* player = players[id];
    player->set_shield(shield_id);
}




void ClientWorld::remove_player(uint16_t id) {
    std::unique_lock<std::mutex> lock(m);
    delete this->players[id];
    this->players.erase(id);
}

ProtocolMessage ClientWorld::player_handle_event(uint16_t &player_id, SDL_Event& e, SDL_Rect &camera) {
    std::unique_lock<std::mutex> lock(m);
    return std::move(this->players[player_id]->handleEvent(e, camera));
}


void ClientWorld::render(uint16_t id, SDL_Rect &camera, int &it) {
    std::unique_lock<std::mutex> lock(m);
    std::map<uint16_t, Player*>::iterator itr;
    for (itr = players.begin(); itr != players.end(); ++itr)  
        itr->second->render(camera, it);

    std::map<uint16_t, NPC*>::iterator npc_itr;
    for (npc_itr = npcs.begin(); npc_itr != npcs.end(); ++npc_itr)  
        npc_itr->second->render(camera);
}



ClientWorld::ClientWorld(ClientWorld&& other) {
    this->players = other.players;
    this->npcs = other.npcs;
    this->gRenderer = other.gRenderer;
}


ClientWorld& ClientWorld::operator=(ClientWorld&& other) {
    this->players = other.players;
    this->npcs = other.npcs;
    this->gRenderer = other.gRenderer;
    return *this;
}

