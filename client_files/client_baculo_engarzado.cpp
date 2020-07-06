
#include "client_baculo_engarzado.h"

BaculoEngarzado::~BaculoEngarzado() {}


BaculoEngarzado::BaculoEngarzado(SDL_Renderer* gRenderer) : Weapon(0) {
    this->load_pictures(gRenderer);
    this->id = 15;
}


bool BaculoEngarzado::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->weaponTexture.loadFromFile( "images/baculo_engarzado_1.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_sprites();
    return true;
}


void BaculoEngarzado::set_sprites() {
    this->load_front_walking_sprite();  
    this->load_back_walking_sprite();
    this->load_left_walking_sprite();
    this->load_right_walking_sprite();
}



void BaculoEngarzado::load_front_walking_sprite() {
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


void BaculoEngarzado::load_back_walking_sprite() {
    SDL_Rect first = {0, 45, 24, 45};
    this->walkingBackPlayer.push_back(first);

    SDL_Rect second = {25, 45, 24, 45};
    this->walkingBackPlayer.push_back(second);

    SDL_Rect third = {50, 45, 24, 45};
    this->walkingBackPlayer.push_back(third);

    SDL_Rect fourth = {75, 45, 24, 45};
    this->walkingBackPlayer.push_back(fourth);

    SDL_Rect fifth = {100, 45, 24, 45};
    this->walkingBackPlayer.push_back(fifth);

    SDL_Rect sixth = {125, 45, 24, 45};
    this->walkingBackPlayer.push_back(sixth);
}


void BaculoEngarzado::load_left_walking_sprite() {
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


void BaculoEngarzado::load_right_walking_sprite() {
    SDL_Rect first = {0, 135, 24, 45};
    this->walkingRightPlayer.push_back(first);

    SDL_Rect second = {27, 135, 24, 45};
    this->walkingRightPlayer.push_back(second);

    SDL_Rect third = {52, 135, 24, 45};
    this->walkingRightPlayer.push_back(third);

    SDL_Rect fourth = {76, 135, 24, 45};
    this->walkingRightPlayer.push_back(fourth);

    SDL_Rect fifth = {102, 135, 24, 45};
    this->walkingRightPlayer.push_back(fifth);
}

