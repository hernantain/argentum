#ifndef _CLIENT_GHOST
#define _CLIENT_GHOST

#include <SDL2/SDL.h>
#include <vector>
#include <stdint.h>

#include "client_texture.h"

class Ghost {

    LTexture bodyTexture;
    LTexture headTexture;
    
    std::vector<SDL_Rect>headOrientations;
    std::vector<SDL_Rect>frontOrientation;
    std::vector<SDL_Rect>backOrientation;
    std::vector<SDL_Rect>leftOrientation;
    std::vector<SDL_Rect>rightOrientation;

    void set_sprites();
    bool load_pictures(SDL_Renderer* gRenderer);

    void load_head_sprite();
    void load_front_walking_sprite();
    void load_left_walking_sprite();
    void load_right_walking_sprite();
    void load_back_walking_sprite();
    public:
        Ghost(SDL_Renderer* gRenderer);

        void render(int16_t posX, int16_t posY, SDL_Renderer* gRenderer, int &orientation, int &frame);

        ~Ghost();

};




#endif
