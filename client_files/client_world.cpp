
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
    std::cout << "Insertando " << id << std::endl;
    this->npcs.insert(std::pair<int16_t, NPC*> (id, npc));
}


void ClientWorld::add_player(ProtocolCharacter &protocolCharacter) {
    std::unique_lock<std::mutex> lock(m);
    Player* player;
    std::cout << "RAZA ES: " << protocolCharacter.id_race << std::endl;
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