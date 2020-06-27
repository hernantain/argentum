#ifndef _CLIENT_HUMAN
#define _CLIENT_HUMAN

#include <SDL2/SDL.h>
#include "client_tall_player.h"


class Human: public TallPlayer {

    public:
        Human(SDL_Renderer* gRenderer);

};


#endif
