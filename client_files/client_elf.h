#ifndef _CLIENT_ELF
#define _CLIENT_ELF

#include <SDL2/SDL.h>
#include "client_tall_player.h"


class Elf: public TallPlayer {

    public:
        Elf(SDL_Renderer* gRenderer);

};


#endif
