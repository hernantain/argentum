
#include "client_npc.h"


bool NPC::load_pictures(const char* picture_path) {
    if( !this->npcTexture.loadFromFile( picture_path, gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    return true;
}


NPC::NPC(int16_t id, SDL_Renderer* gRenderer) : Drawable (id, gRenderer) {}
