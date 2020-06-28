#ifndef _CLIENT_SWORD
#define _CLIENT_SWORD

#include <SDL2/SDL.h>
#include "client_weapon.h"


class Sword : public Weapon {

    void set_sprites();

    void load_front_walking_sprite();
    void load_left_walking_sprite();
    void load_right_walking_sprite();
    void load_back_walking_sprite();

    public:
        Sword(SDL_Renderer* gRenderer);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

        ~Sword();

};


#endif

