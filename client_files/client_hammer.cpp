
#include "client_hammer.h"


Hammer::Hammer(SDL_Renderer* gRenderer) : Weapon(0) {
    this->load_pictures(gRenderer); 
}

Hammer::~Hammer() {}


void Hammer::set_sprites() {
    this->load_front_walking_sprite();  
    this->load_back_walking_sprite();
    this->load_left_walking_sprite();
    this->load_right_walking_sprite();
}



bool Hammer::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->weaponTexture.loadFromFile( "images/martillo.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_sprites();
    return true;
}


void Hammer::load_front_walking_sprite() {
    this->walkingFrontPlayer[0].x = 0;
    this->walkingFrontPlayer[0].y = 0;
    this->walkingFrontPlayer[0].w = 24;
    this->walkingFrontPlayer[0].h = 45;

    this->walkingFrontPlayer[1].x = 24;
    this->walkingFrontPlayer[1].y = 0;
    this->walkingFrontPlayer[1].w = 24;
    this->walkingFrontPlayer[1].h = 45;

    this->walkingFrontPlayer[2].x = 48;
    this->walkingFrontPlayer[2].y = 0;
    this->walkingFrontPlayer[2].w = 24;
    this->walkingFrontPlayer[2].h = 45;

    this->walkingFrontPlayer[3].x = 72;
    this->walkingFrontPlayer[3].y = 0;
    this->walkingFrontPlayer[3].w = 24;
    this->walkingFrontPlayer[3].h = 45;

    this->walkingFrontPlayer[4].x = 96;
    this->walkingFrontPlayer[4].y = 0;
    this->walkingFrontPlayer[4].w = 24;
    this->walkingFrontPlayer[4].h = 45;

    this->walkingFrontPlayer[5].x = 120;
    this->walkingFrontPlayer[5].y = 0;
    this->walkingFrontPlayer[5].w = 24;
    this->walkingFrontPlayer[5].h = 45;
}


void Hammer::load_back_walking_sprite() {
    this->walkingBackPlayer[0].x = 0;
    this->walkingBackPlayer[0].y = 45;
    this->walkingBackPlayer[0].w = 24;
    this->walkingBackPlayer[0].h = 45;

    this->walkingBackPlayer[1].x = 26;
    this->walkingBackPlayer[1].y = 45;
    this->walkingBackPlayer[1].w = 24;
    this->walkingBackPlayer[1].h = 45;

    this->walkingBackPlayer[2].x = 52;
    this->walkingBackPlayer[2].y = 45;
    this->walkingBackPlayer[2].w = 24;
    this->walkingBackPlayer[2].h = 45;

    this->walkingBackPlayer[3].x = 78;
    this->walkingBackPlayer[3].y = 45;
    this->walkingBackPlayer[3].w = 24;
    this->walkingBackPlayer[3].h = 45;

    this->walkingBackPlayer[4].x = 102;
    this->walkingBackPlayer[4].y = 45;
    this->walkingBackPlayer[4].w = 24;
    this->walkingBackPlayer[4].h = 45;

    this->walkingBackPlayer[5].x = 125;
    this->walkingBackPlayer[5].y = 45;
    this->walkingBackPlayer[5].w = 24;
    this->walkingBackPlayer[5].h = 45;
}


void Hammer::load_left_walking_sprite() {
    this->walkingLeftPlayer[0].x = 0;
    this->walkingLeftPlayer[0].y = 90;
    this->walkingLeftPlayer[0].w = 24;
    this->walkingLeftPlayer[0].h = 45;

    this->walkingLeftPlayer[1].x = 24;
    this->walkingLeftPlayer[1].y = 90;
    this->walkingLeftPlayer[1].w = 24;
    this->walkingLeftPlayer[1].h = 45;

    this->walkingLeftPlayer[2].x = 48;
    this->walkingLeftPlayer[2].y = 90;
    this->walkingLeftPlayer[2].w = 24;
    this->walkingLeftPlayer[2].h = 45;

    this->walkingLeftPlayer[3].x = 72;
    this->walkingLeftPlayer[3].y = 90;
    this->walkingLeftPlayer[3].w = 24;
    this->walkingLeftPlayer[3].h = 45;

    this->walkingLeftPlayer[4].x = 96;
    this->walkingLeftPlayer[4].y = 90;
    this->walkingLeftPlayer[4].w = 24;
    this->walkingLeftPlayer[4].h = 45;
}


void Hammer::load_right_walking_sprite() {
    this->walkingRightPlayer[0].x = 0;
    this->walkingRightPlayer[0].y = 135;
    this->walkingRightPlayer[0].w = 24;
    this->walkingRightPlayer[0].h = 45;

    this->walkingRightPlayer[1].x = 26;
    this->walkingRightPlayer[1].y = 135;
    this->walkingRightPlayer[1].w = 24;
    this->walkingRightPlayer[1].h = 45;

    this->walkingRightPlayer[2].x = 52;
    this->walkingRightPlayer[2].y = 135;
    this->walkingRightPlayer[2].w = 24;
    this->walkingRightPlayer[2].h = 45;

    this->walkingRightPlayer[3].x = 75;
    this->walkingRightPlayer[3].y = 135;
    this->walkingRightPlayer[3].w = 24;
    this->walkingRightPlayer[3].h = 45;

    this->walkingRightPlayer[4].x = 102;
    this->walkingRightPlayer[4].y = 135;
    this->walkingRightPlayer[4].w = 24;
    this->walkingRightPlayer[4].h = 45;
}