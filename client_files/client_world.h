#ifndef _CLIENT_WORLD
#define _CLIENT_WORLD

#include "client_player.h"
#include <map>
#include <SDL2/SDL.h>
#include <stdint.h>


struct ClientWorld {
    SDL_Renderer *gRenderer;

    std::map<int16_t, Player*> players;

    ClientWorld(SDL_Renderer *gRenderer);

    void add_player(int16_t id, Player* player);

    void add_player(ProtocolCharacter &protocolCharacter);

};



#endif
