#ifndef _CLIENT_ASH_STAFF
#define _CLIENT_ASH_STAFF

#include <SDL2/SDL.h>
#include "client_weapon.h"


class AshStaff: public Weapon {

    void set_sprites();

    void load_front_walking_sprite();
    void load_left_walking_sprite();
    void load_right_walking_sprite();
    void load_back_walking_sprite();

    public:
        AshStaff(SDL_Renderer* gRenderer);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

        virtual ~AshStaff();


};



#endif
