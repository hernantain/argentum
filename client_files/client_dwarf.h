#ifndef _CLIENT_DWARF
#define _CLIENT_DWARF

#include "client_short_player.h"
#include <SDL2/SDL.h>


class Dwarf: public ShortPlayer {

    public: 
        Dwarf(SDL_Renderer* gRenderer);

};


#endif
