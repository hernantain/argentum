#ifndef _CLIENT_IRON_SHIELD
#define _CLIENT_IRON_SHIELD

#include "client_weapon.h"
#include <SDL2/SDL.h>


class IronShield: public Weapon {

    void set_sprites();

    void load_front_walking_sprite();
    void load_left_walking_sprite();
    void load_right_walking_sprite();
    void load_back_walking_sprite();

    public:
        IronShield(SDL_Renderer* gRenderer);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

        ~IronShield();
};


#endif
