
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
    

void ClientWorld::add_player(int16_t id, Player* player) {
    std::cout << "Insertando " << id << std::endl;
    this->players.insert(std::pair<int16_t, Player*> (id, player));
}

void ClientWorld::add_npc(int16_t id, NPC* npc) {
    // std::cout << "Insertando " << id << std::endl;
    this->npcs.insert(std::pair<int16_t, NPC*> (id, npc));
}


Player* ClientWorld::get_player(int16_t id) {
    std::unique_lock<std::mutex> lock(m);
    return this->players[id];
}


void ClientWorld::add_player(ProtocolCharacter &protocolCharacter) {
    std::unique_lock<std::mutex> lock(m);
    Player* player;
    
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


void ClientWorld::remove_player(int16_t id) {
    std::unique_lock<std::mutex> lock(m);
    delete this->players[id];
    this->players.erase(id);
}

ProtocolMessage ClientWorld::player_handle_event(uint16_t &player_id, SDL_Event& e, SDL_Rect &camera) {
    std::unique_lock<std::mutex> lock(m);
    return std::move(this->players[player_id]->handleEvent(e, camera));
}


void ClientWorld::render(int16_t id, SDL_Rect &camera, int &it) {
    std::unique_lock<std::mutex> lock(m);
    std::map<int16_t, Player*>::iterator itr;
    for (itr = players.begin(); itr != players.end(); ++itr)  
        itr->second->render(camera, it);

    std::map<int16_t, NPC*>::iterator npc_itr;
    for (npc_itr = npcs.begin(); npc_itr != npcs.end(); ++npc_itr)  
        npc_itr->second->render(camera);

}



ClientWorld::ClientWorld(ClientWorld&& other) {
    this->players = std::move(other.players);
    this->npcs = std::move(other.npcs);
    this->gRenderer = other.gRenderer;
}


ClientWorld& ClientWorld::operator=(ClientWorld&& other) {
    this->players = std::move(other.players);
    this->npcs = std::move(other.npcs);
    this->gRenderer = other.gRenderer;
    return *this;
}