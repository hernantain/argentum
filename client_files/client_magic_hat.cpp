
#include "client_magic_hat.h"


MagicHat::MagicHat(SDL_Renderer* gRenderer) : Helmet(-12) {

    this->load_pictures(gRenderer); 

}


bool MagicHat::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->helmetTexture.loadFromFile( "images/sombrero_magico.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_sprites();
    return true;
}


void MagicHat::set_sprites() {
	this->helmetOrientation[0].x = 0;
	this->helmetOrientation[0].y = 2;
	this->helmetOrientation[0].h = 17;
	this->helmetOrientation[0].w = 18;

	this->helmetOrientation[1].x = 17;
	this->helmetOrientation[1].y = 0;
	this->helmetOrientation[1].h = 17;
	this->helmetOrientation[1].w = 18;

	this->helmetOrientation[2].x = 34;
	this->helmetOrientation[2].y = 2;
	this->helmetOrientation[2].h = 17;
	this->helmetOrientation[2].w = 18;

	this->helmetOrientation[3].x = 51;
	this->helmetOrientation[3].y = 2;
	this->helmetOrientation[3].h = 17;
	this->helmetOrientation[3].w = 18;
}
