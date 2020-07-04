#ifndef _CLIENT_WEAPON
#define _CLIENT_WEAPON

#include "client_texture.h"
#include <SDL2/SDL.h>


#define WALKING_FRONT_ANIMATION_FRAMES 6
#define WALKING_BACK_ANIMATION_FRAMES 6
#define WALKING_LEFT_ANIMATION_FRAMES 5
#define WALKING_RIGHT_ANIMATION_FRAMES 5


class Weapon {

    int offset;
    
    protected:
        int id;
        Weapon(int offset);
        LTexture weaponTexture;
        SDL_Rect walkingFrontPlayer[ WALKING_FRONT_ANIMATION_FRAMES ];
        SDL_Rect walkingBackPlayer[ WALKING_BACK_ANIMATION_FRAMES ];
        SDL_Rect walkingLeftPlayer[ WALKING_LEFT_ANIMATION_FRAMES ];
        SDL_Rect walkingRightPlayer[ WALKING_RIGHT_ANIMATION_FRAMES ];

        virtual bool load_pictures(SDL_Renderer* gRenderer) = 0;

        // virtual void set_sprites();

        // virtual void load_front_walking_sprite();
        // virtual void load_left_walking_sprite();
        // virtual void load_right_walking_sprite();
        // virtual void load_back_walking_sprite();

    public:
        virtual void render(int &bodyPosX, int &bodyPosY, SDL_Renderer* gRenderer, int &orientation, int &frame);

        int get_id();

        virtual ~Weapon();

};


#endif
