
#include "client_sword.h"


Sword::Sword(SDL_Renderer* gRenderer) : Weapon(0) {
    this->load_pictures(gRenderer);
    this->id = 9;
}


Sword::~Sword() {}


bool Sword::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->weaponTexture.loadFromFile( "media/images/espada2.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_sprites();
    return true;
}


void Sword::set_sprites() {
    this->load_front_walking_sprite();  
    this->load_back_walking_sprite();
    this->load_left_walking_sprite();
    this->load_right_walking_sprite();
}



void Sword::load_front_walking_sprite() {

    SDL_Rect first = {0, 0, 24, 45};
    this->walkingFrontPlayer.push_back(first);

    SDL_Rect second = {24, 0, 24, 45};
    this->walkingFrontPlayer.push_back(second);

    SDL_Rect third = {48, 0, 24, 45};
    this->walkingFrontPlayer.push_back(third);

    SDL_Rect fourth = {72, 0, 24, 45};
    this->walkingFrontPlayer.push_back(fourth);

    SDL_Rect fifth = {96, 0, 24, 45};
    this->walkingFrontPlayer.push_back(fifth);

    SDL_Rect sixth = {120, 0, 24, 45};
    this->walkingFrontPlayer.push_back(sixth);
}


void Sword::load_back_walking_sprite() {

    SDL_Rect first = {0, 45, 24, 45};
    this->walkingBackPlayer.push_back(first);

    SDL_Rect second = {24, 45, 24, 45};
    this->walkingBackPlayer.push_back(second);

    SDL_Rect third = {48, 45, 24, 45};
    this->walkingBackPlayer.push_back(third);

    SDL_Rect fourth = {72, 45, 24, 45};
    this->walkingBackPlayer.push_back(fourth);

    SDL_Rect fifth = {96, 45, 24, 45};
    this->walkingBackPlayer.push_back(fifth);

    SDL_Rect sixth = {120, 45, 24, 45};
    this->walkingBackPlayer.push_back(sixth);
}


void Sword::load_left_walking_sprite() {

    SDL_Rect first = {0, 90, 24, 45};
    this->walkingLeftPlayer.push_back(first);

    SDL_Rect second = {24, 90, 24, 45};
    this->walkingLeftPlayer.push_back(second);

    SDL_Rect third = {48, 90, 24, 45};
    this->walkingLeftPlayer.push_back(third);

    SDL_Rect fourth = {72, 90, 24, 45};
    this->walkingLeftPlayer.push_back(fourth);

    SDL_Rect fifth = {96, 90, 24, 45};
    this->walkingLeftPlayer.push_back(fifth);
}


void Sword::load_right_walking_sprite() {
    SDL_Rect first = {0, 135, 24, 45};
    this->walkingRightPlayer.push_back(first);

    SDL_Rect second = {24, 135, 24, 45};
    this->walkingRightPlayer.push_back(second);

    SDL_Rect third = {48, 135, 24, 45};
    this->walkingRightPlayer.push_back(third);

    SDL_Rect fourth = {72, 135, 24, 45};
    this->walkingRightPlayer.push_back(fourth);

    SDL_Rect fifth = {96, 135, 24, 45};
    this->walkingRightPlayer.push_back(fifth);
}
