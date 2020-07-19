#ifndef _CLIENT_MAGIC_HAT
#define _CLIENT_MAGIC_HAT

#include <SDL2/SDL.h>
#include "client_helmet.h"


class MagicHat: public Helmet {

    void set_sprites();
    public:
        MagicHat(SDL_Renderer* gRenderer);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

        virtual ~MagicHat();

};



#endif
