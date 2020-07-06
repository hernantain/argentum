#ifndef _CLIENT_CLOTHES
#define _CLIENT_CLOTHES

#define WALKING_FRONT_ANIMATION_FRAMES 6
#define WALKING_BACK_ANIMATION_FRAMES 6
#define WALKING_LEFT_ANIMATION_FRAMES 5
#define WALKING_RIGHT_ANIMATION_FRAMES 5

#include <SDL2/SDL.h>
#include <vector>
#include "client_texture.h"

class Clothes {
    
    int width, height;

    void load_front_walking_sprite();
    void load_left_walking_sprite();
    void load_right_walking_sprite();
    void load_back_walking_sprite();

    void loadTallWalkingFrontSprite();
    void loadTallWalkingBackSprite();
    void loadTallWalkingLeftSprite();
    void loadTallWalkingRightSprite();

    protected:
        int id;
        LTexture bodyTexture;
        std::vector<SDL_Rect> walkingFrontPlayer;
        std::vector<SDL_Rect> walkingBackPlayer;
        std::vector<SDL_Rect> walkingLeftPlayer;
        std::vector<SDL_Rect> walkingRightPlayer;

        virtual bool load_pictures(SDL_Renderer* gRenderer) = 0;
        void set_tall_sprites();
        void set_short_sprites();

        Clothes(int width, int height);
        
    public:
        virtual void render(int &bodyPosX, int &bodyPosY, SDL_Renderer* gRenderer, int &orientation, int &frame);

        int get_id();
};




#endif

