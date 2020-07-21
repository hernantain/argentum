
#include "client_blue_robe.h"


BlueTallRobe::BlueTallRobe(
    SDL_Renderer* gRenderer, 
    int width, 
    int height) : Clothes(width, height) {

    this->load_pictures(gRenderer);
    this->id = 3;
}


bool BlueTallRobe::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->bodyTexture.loadFromFile( "media/images/tunica_azul_he.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_tall_sprites();
    return true;
}


BlueTallRobe::~BlueTallRobe() {}



BlueShortRobe::BlueShortRobe(
    SDL_Renderer* gRenderer, 
    int width, 
    int height) : Clothes(width, height) {

    this->load_pictures(gRenderer);
    this->id = 3;
}


bool BlueShortRobe::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->bodyTexture.loadFromFile( "media/images/tunica_azul_eg.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_short_sprites();
    return true;
}

BlueShortRobe::~BlueShortRobe() {}
