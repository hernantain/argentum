#ifndef _CLIENT_BACULO_ENGARZADO
#define _CLIENT_BACULO_ENGARZADO

#include "client_weapon.h"
#include <SDL2/SDL.h>


class BaculoEngarzado: public Weapon {

    void set_sprites();

    void load_front_walking_sprite();
    void load_left_walking_sprite();
    void load_right_walking_sprite();
    void load_back_walking_sprite();

    public:
        BaculoEngarzado(SDL_Renderer* gRenderer);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

        virtual ~BaculoEngarzado() override;

};






#endif
