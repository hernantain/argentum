
#include "client_leather_armor.h"


LeatherTallArmor::LeatherTallArmor(
    SDL_Renderer* gRenderer, 
    int width, 
    int height) : Clothes(width, height) {

    this->load_pictures(gRenderer);
    this->id = 1;

}

bool LeatherTallArmor::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->bodyTexture.loadFromFile( "media/images/armadura_cuero_he.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_tall_sprites();
    return true;
}

LeatherTallArmor::~LeatherTallArmor() {}




LeatherShortArmor::LeatherShortArmor(
    SDL_Renderer* gRenderer, 
    int width, 
    int height) : Clothes(width, height) {

    this->load_pictures(gRenderer);
    this->id = 1;

}

bool LeatherShortArmor::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->bodyTexture.loadFromFile( "media/images/armadura_cuero_eg.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_short_sprites();
    return true;   
}

LeatherShortArmor::~LeatherShortArmor() {}
