
#include "client_npc_picture.h"


bool NpcPicture::load_pictures(const char* picture_path) {
    if( !this->npcTexture.loadFromFile( picture_path, gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    return true;
}


NpcPicture::NpcPicture(SDL_Renderer* gRenderer) {
    this->gRenderer = gRenderer;
}
