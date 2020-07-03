
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
    this->players.insert(std::pair<int16_t, Player*> (id, player));
}


void ClientWorld::add_player(ProtocolCharacter &protocolCharacter) {
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
