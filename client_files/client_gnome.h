#ifndef _CLIENT_GNOME
#define _CLIENT_GNOME

#include "client_short_player.h"
#include <SDL2/SDL.h>
#include <stdint.h>


class Gnome: public ShortPlayer {

    public: 
        Gnome(SDL_Renderer* gRenderer, int16_t id, int bodyPosX, int bodyPosY);

};


#endif
