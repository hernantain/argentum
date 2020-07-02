#ifndef _CLIENT_WORLD
#define _CLIENT_WORLD

#include "client_player.h"
#include <map>
#include <stdint.h>


struct ClientWorld {

    std::map<int16_t, Player*> players;

    ClientWorld();


};



#endif
