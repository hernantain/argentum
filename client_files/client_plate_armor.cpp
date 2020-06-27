
#include "client_plate_armor.h"


PlateTallArmor::PlateTallArmor(
    SDL_Renderer* gRenderer, 
    int width, 
    int height) : Clothes(width, height) {

    this->load_pictures(gRenderer); 

}


bool PlateTallArmor::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->bodyTexture.loadFromFile( "images/armadura_placas_he.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_tall_sprites();
    return true;
}


PlateShortArmor::PlateShortArmor(
    SDL_Renderer* gRenderer, 
    int width, 
    int height) : Clothes(width, height) {

    this->load_pictures(gRenderer); 

}


bool PlateShortArmor::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->bodyTexture.loadFromFile( "images/armadura_placas_eg.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_short_sprites();
    return true;
}
