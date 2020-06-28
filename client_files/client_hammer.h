#ifndef _CLIENT_HAMMER
#define _CLIENT_HAMMER


#include "client_weapon.h"
#include <SDL2/SDL.h>


class Hammer: public Weapon {

    void set_sprites();

    void load_front_walking_sprite();
    void load_left_walking_sprite();
    void load_right_walking_sprite();
    void load_back_walking_sprite();

    public:
        Hammer(SDL_Renderer* gRenderer);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

        virtual ~Hammer() override;

};





#endif
