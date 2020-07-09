#ifndef _CLIENT_NPC
#define _CLIENT_NPC

#include <stdint.h>
#include <SDL2/SDL.h>

#include "client_drawable.h"
#include "client_texture.h"
#include "client_npc_picture.h"

class NPC: public Drawable {

    public:
        uint16_t npc_id;
        int16_t posX, posY;
        NpcPicture* npcPicture;

        NPC(int16_t id, int16_t npc_id, SDL_Renderer* gRenderer, int16_t posX, int16_t posY);

        // TODO: add orientation
        // void set_position(int newBodyPosX, int newBodyPosY, int orientation);
		void set_position(int newPosX, int newPosY);


        void render(SDL_Rect &camera);


};


#endif
