#ifndef _CLIENT_GOBLIN
#define _CLIENT_GOBLIN

#include <stdint.h>
#include <SDL2/SDL.h>
#include "client_npc_picture.h"



class Goblin: public NpcPicture {

    // virtual bool load_pictures(const char* picture_path);
    virtual void load_front_walking_sprite() override;  
    virtual void load_back_walking_sprite() override;
    virtual void load_left_walking_sprite() override;
    virtual void load_right_walking_sprite() override;
    virtual void set_sprites() override;
    SDL_Rect leftOrientation[8];
    SDL_Rect rightOrientation[8];
    SDL_Rect frontOrientation[8];
    SDL_Rect backOrientation[8];
    
    public:
        Goblin(SDL_Renderer* gRenderer);

        virtual void render(int posX, int posY, SDL_Renderer* gRenderer, int &orientation, int &frame) override;

        virtual ~Goblin();

};




#endif
