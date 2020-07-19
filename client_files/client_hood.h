#ifndef _CLIENT_HOOD
#define _CLIENT_HOOD

#include "client_helmet.h"
#include <SDL2/SDL.h>


class Hood: public Helmet {

    void set_sprites();
    public:
        Hood(SDL_Renderer* gRenderer);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

        virtual ~Hood();

};



#endif
