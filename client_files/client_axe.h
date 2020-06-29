#ifndef _CLIENT_AXE
#define _CLIENT_AXE


#include "client_weapon.h"
#include <SDL2/SDL.h>


class Axe: public Weapon {

    void set_sprites();

    void load_front_walking_sprite();
    void load_left_walking_sprite();
    void load_right_walking_sprite();
    void load_back_walking_sprite();

    public:
        Axe(SDL_Renderer* gRenderer);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

        virtual ~Axe() override;

};


#endif
