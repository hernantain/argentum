#ifndef _CLIENT_ELF
#define _CLIENT_ELF

#include <SDL2/SDL.h>
#include <stdint.h>
#include "client_tall_player.h"


class Elf: public TallPlayer {

    public:
        Elf(SDL_Renderer* gRenderer, int16_t id, int bodyPosX, int bodyPosY);

};


#endif
