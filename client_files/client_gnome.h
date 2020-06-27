#ifndef _CLIENT_GNOME
#define _CLIENT_GNOME

#include "client_short_player.h"
#include <SDL2/SDL.h>


class Gnome: public ShortPlayer {

    public: 
        Gnome(SDL_Renderer* gRenderer);

};


#endif
