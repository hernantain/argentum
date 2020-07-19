#ifndef _CLIENT_BACULO_NUDOSO
#define _CLIENT_BACULO_NUDOSO


#include "client_weapon.h"
#include <SDL2/SDL.h>


class BaculoNudoso: public Weapon {

    void set_sprites();

    void load_front_walking_sprite();
    void load_left_walking_sprite();
    void load_right_walking_sprite();
    void load_back_walking_sprite();

    public:
        BaculoNudoso(SDL_Renderer* gRenderer);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

        virtual ~BaculoNudoso();


};




#endif
