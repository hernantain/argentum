#ifndef _CLIENT_TURTLE_SHIELD
#define _CLIENT_TURTLE_SHIELD


#include "client_shield.h"
#include <SDL2/SDL.h>


class TurtleShield: public Shield {

    void set_sprites();

    void load_front_walking_sprite();
    void load_left_walking_sprite();
    void load_right_walking_sprite();
    void load_back_walking_sprite();

    public:
        TurtleShield(SDL_Renderer* gRenderer);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

        ~TurtleShield();
};


#endif
