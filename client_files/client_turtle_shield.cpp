
#include "client_turtle_shield.h"


TurtleShield::TurtleShield(SDL_Renderer* gRenderer) : Shield(0) {
    this->load_pictures(gRenderer);
    this->id = 7;
}


TurtleShield::~TurtleShield() {}


bool TurtleShield::load_pictures(SDL_Renderer* gRenderer) {
    if( !this->shieldTexture.loadFromFile( "images/escudo_tortuga.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_sprites();
    return true;
}


void TurtleShield::set_sprites() {
    this->load_front_walking_sprite();  
    this->load_back_walking_sprite();
    this->load_left_walking_sprite();
    this->load_right_walking_sprite();
}



void TurtleShield::load_front_walking_sprite() {
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


void TurtleShield::load_back_walking_sprite() {
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


void TurtleShield::load_left_walking_sprite() {
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


void TurtleShield::load_right_walking_sprite() {
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
