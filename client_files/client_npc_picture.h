#ifndef _CLIENT_NPC_PICTURE
#define _CLIENT_NPC_PICTURE

#include "SDL2/SDL.h"
#include "client_texture.h"
#include "client_drawable.h"


class NpcPicture {

    SDL_Renderer* gRenderer;
    protected:
        LTexture npcTexture;

        NpcPicture(SDL_Renderer* gRenderer);

        virtual bool load_pictures(const char* picture_path);
        virtual void set_sprites() = 0;
        virtual void load_front_walking_sprite() = 0;  
        virtual void load_back_walking_sprite() = 0;
        virtual void load_left_walking_sprite() = 0;
        virtual void load_right_walking_sprite() = 0;
        
    public:
        virtual void render(int posX, int posY, SDL_Renderer* gRenderer, int &orientation, int &frame) = 0;

        virtual ~NpcPicture();

};


#endif
