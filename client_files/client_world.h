#ifndef _CLIENT_WORLD
#define _CLIENT_WORLD

#include "client_player.h"
#include <map>
#include <stdint.h>


struct ClientWorld {

    std::map<int16_t, Player*> players;

    ClientWorld();

    void add_player(int16_t id, Player* player);

};



#endif
