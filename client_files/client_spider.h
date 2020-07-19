#ifndef _CLIENT_SPIDER
#define _CLIENT_SPIDER

#include <stdint.h>
#include <SDL2/SDL.h>
#include "client_npc_picture.h"


class Spider: public NpcPicture {

    virtual void load_front_walking_sprite() override;  
    virtual void load_back_walking_sprite() override;
    virtual void load_left_walking_sprite() override;
    virtual void load_right_walking_sprite() override;
    virtual void set_sprites() override;
    SDL_Rect leftOrientation[4];
    SDL_Rect rightOrientation[4];
    SDL_Rect frontOrientation[4];
    SDL_Rect backOrientation[4];
    public:
        Spider(SDL_Renderer* gRenderer);

        virtual void render(int posX, int posY, SDL_Renderer* gRenderer, int &orientation, int &frame) override;

        virtual ~Spider();


};



#endif
