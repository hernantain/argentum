#ifndef _CLIENT_SKELETON
#define _CLIENT_SKELETON

#include <stdint.h>
#include <SDL2/SDL.h>
#include "client_npc_picture.h"



class Skeleton: public NpcPicture {

    // virtual bool load_pictures(const char* picture_path);
    virtual void load_front_walking_sprite() override;  
    virtual void load_back_walking_sprite() override;
    virtual void load_left_walking_sprite() override;
    virtual void load_right_walking_sprite() override;
    virtual void set_sprites() override;
    SDL_Rect leftOrientation[5];
    SDL_Rect rightOrientation[5];
    SDL_Rect frontOrientation[6];
    SDL_Rect backOrientation[6];
    public:
        Skeleton(SDL_Renderer* gRenderer);

        virtual void render(int posX, int posY, SDL_Renderer* gRenderer, int &orientation, int &frame) override;

        virtual ~Skeleton();

};




#endif
