
#include "client_hood.h"


Hood::Hood(SDL_Renderer* gRenderer) : Helmet(-2) {

    this->load_pictures(gRenderer); 

}


bool Hood::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->helmetTexture.loadFromFile( "images/capucha.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_sprites();
    return true;
}


void Hood::set_sprites() {
	this->helmetOrientation[0].x = 0;
	this->helmetOrientation[0].y = 0;
	this->helmetOrientation[0].h = 17;
	this->helmetOrientation[0].w = 17;

	this->helmetOrientation[1].x = 17;
	this->helmetOrientation[1].y = 0;
	this->helmetOrientation[1].h = 17;
	this->helmetOrientation[1].w = 17;

	this->helmetOrientation[2].x = 35;
	this->helmetOrientation[2].y = 0;
	this->helmetOrientation[2].h = 17;
	this->helmetOrientation[2].w = 17;

	this->helmetOrientation[3].x = 51;
	this->helmetOrientation[3].y = 0;
	this->helmetOrientation[3].h = 17;
	this->helmetOrientation[3].w = 17;
}
