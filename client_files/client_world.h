#ifndef _CLIENT_WORLD
#define _CLIENT_WORLD

#include <map>
#include <SDL2/SDL.h>
#include <stdint.h>

#include "client_player.h"
#include "client_npc.h"


struct ClientWorld {
    SDL_Renderer *gRenderer;
    std::mutex m;

    std::map<int16_t, Player*> players;
    std::map<int16_t, NPC*> npcs;

    ClientWorld(SDL_Renderer *gRenderer);

    void add_player(int16_t id, Player* player);

    void add_npc(int16_t id, NPC* npc);

    void add_player(ProtocolCharacter &protocolCharacter);

    void add_npc(ProtocolNpc &protocolNpc);

    void render(int16_t id, SDL_Rect &camera);


    ClientWorld(ClientWorld&& other);
    ClientWorld& operator=(ClientWorld&& other);

    ClientWorld(const ClientWorld&) = delete;
    ClientWorld& operator=(const ClientWorld&) = delete;

};



#endif
