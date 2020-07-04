#ifndef _CLIENT_GOBLIN
#define _CLIENT_GOBLIN

#include <stdint.h>
#include <SDL2/SDL.h>
#include "client_npc.h"



class Goblin: public NPC {

    // virtual bool load_pictures(const char* picture_path);
    virtual void load_front_walking_sprite();  
    virtual void load_back_walking_sprite();
    virtual void load_left_walking_sprite();
    virtual void load_right_walking_sprite();
    virtual void set_sprites();
    SDL_Rect leftOrientation[8];
    SDL_Rect rightOrientation[8];
    SDL_Rect frontOrientation[8];
    SDL_Rect backOrientation[8];
    
    public:
        Goblin(int16_t id, SDL_Renderer* gRenderer);

};




#endif
