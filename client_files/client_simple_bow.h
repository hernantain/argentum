#ifndef _CLIENT_SIMPLE_BOW
#define _CLIENT_SIMPLE_BOW


#include <SDL2/SDL.h>
#include "client_weapon.h"


class SimpleBow: public Weapon {


    void set_sprites();

    void load_front_walking_sprite();
    void load_left_walking_sprite();
    void load_right_walking_sprite();
    void load_back_walking_sprite();

    public:
        SimpleBow(SDL_Renderer* gRenderer);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

        ~SimpleBow();


};




#endif
