#ifndef _CLIENT_WEAPON
#define _CLIENT_WEAPON

#include "client_texture.h"
#include <SDL2/SDL.h>
#include <vector>


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
        std::vector<SDL_Rect> walkingFrontPlayer;
        std::vector<SDL_Rect> walkingBackPlayer;
        std::vector<SDL_Rect> walkingLeftPlayer;
        std::vector<SDL_Rect> walkingRightPlayer;

        virtual bool load_pictures(SDL_Renderer* gRenderer) = 0;

    public:
        virtual void render(int &bodyPosX, int &bodyPosY, SDL_Renderer* gRenderer, int &orientation, int &frame);

        int get_id();

        virtual ~Weapon();

};


#endif
