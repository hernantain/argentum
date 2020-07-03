#ifndef _CLIENT_HUMAN
#define _CLIENT_HUMAN

#include <SDL2/SDL.h>
#include <stdint.h>
#include "client_tall_player.h"


class Human: public TallPlayer {

    public:
        Human(SDL_Renderer* gRenderer, int16_t id, int bodyPosX, int bodyPosY);

};


#endif
