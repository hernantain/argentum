#ifndef _CLIENT_IRON_HELMET
#define _CLIENT_IRON_HELMET

#include "client_helmet.h"
#include <SDL2/SDL.h>

class IronHelmet: public Helmet {

    void set_sprites();
    public:
        IronHelmet(SDL_Renderer* gRenderer);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

        virtual ~IronHelmet();

};

#endif

