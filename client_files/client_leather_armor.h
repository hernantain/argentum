#ifndef _CLIENT_LEATHER_ARMOR
#define _CLIENT_LEATHER_ARMOR

#include "client_clothes.h"
#include <SDL2/SDL.h>

class LeatherTallArmor: public Clothes {

    public:
        LeatherTallArmor(SDL_Renderer* gRenderer, int width, int height);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;
};


class LeatherShortArmor: public Clothes {

    public:
        LeatherShortArmor(SDL_Renderer* gRenderer, int width, int height);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;
};



#endif
