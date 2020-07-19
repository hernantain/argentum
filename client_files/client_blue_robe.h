#ifndef _CLIENT_BLUE_ROBE
#define _CLIENT_BLUE_ROBE

#include "client_clothes.h"
#include <SDL2/SDL.h>

class BlueTallRobe: public Clothes {

    public:
        BlueTallRobe(SDL_Renderer* gRenderer, int width, int height);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

        virtual ~BlueTallRobe();
};



class BlueShortRobe: public Clothes {

    public:
        BlueShortRobe(SDL_Renderer* gRenderer, int width, int height);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

        virtual ~BlueShortRobe();        
};

#endif
