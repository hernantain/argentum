#ifndef _CLIENT_SPIDER
#define _CLIENT_SPIDER

#include <stdint.h>
#include <SDL2/SDL.h>
#include "client_npc.h"


class Spider: public NPC {

    virtual void load_front_walking_sprite();  
    virtual void load_back_walking_sprite();
    virtual void load_left_walking_sprite();
    virtual void load_right_walking_sprite();
    virtual void set_sprites();
    SDL_Rect leftOrientation[4];
    SDL_Rect rightOrientation[4];
    SDL_Rect frontOrientation[4];
    SDL_Rect backOrientation[4];
    public:
        Spider(int16_t id, SDL_Renderer* gRenderer);


};



#endif
