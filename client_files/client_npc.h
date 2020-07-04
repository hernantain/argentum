#ifndef _CLIENT_NPC
#define _CLIENT_NPC

#include <stdint.h>
#include <SDL2/SDL.h>

#include "client_drawable.h"
#include "client_texture.h"


class NPC: public Drawable {

    protected:
        uint16_t npc_id;
        LTexture npcTexture;

        NPC(int16_t id, SDL_Renderer* gRenderer);

        virtual bool load_pictures(const char* picture_path);
        virtual void set_sprites() = 0;
        virtual void load_front_walking_sprite() = 0;  
        virtual void load_back_walking_sprite() = 0;
        virtual void load_left_walking_sprite() = 0;
        virtual void load_right_walking_sprite() = 0;

};


#endif
