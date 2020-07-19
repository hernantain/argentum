#ifndef _CLIENT_PLATE_ARMOR
#define _CLIENT_PLATE_ARMOR

#include "client_clothes.h"
#include <SDL2/SDL.h>

class PlateTallArmor: public Clothes {

    public:
        PlateTallArmor(SDL_Renderer* gRenderer, int width, int height);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

        virtual ~PlateTallArmor();
};



class PlateShortArmor: public Clothes {

    public:
        PlateShortArmor(SDL_Renderer* gRenderer, int width, int height);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

        virtual ~PlateShortArmor();
};

#endif
