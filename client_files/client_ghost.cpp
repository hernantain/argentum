
#include <iostream>
#include "client_ghost.h"
#include "client_drawable.h"


Ghost::Ghost(SDL_Renderer* gRenderer) {
    this->load_pictures(gRenderer);
}

Ghost::~Ghost() {
    std::cout << "Destruyendo Ghost" << std::endl;
    bodyTexture.free();
    headTexture.free();
}

bool Ghost::load_pictures(SDL_Renderer* gRenderer) {

    if( !this->bodyTexture.loadFromFile( "images/ghost.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}


    if( !this->headTexture.loadFromFile( "images/ghost_head.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_sprites();
    return true;
}


void Ghost::render(int16_t bodyPosX, int16_t bodyPosY, SDL_Renderer* gRenderer, int &orientation, int &frame) {

    SDL_Rect *currentClip, *headClip;
	if (orientation == RIGHT) {
        headClip = &this->headOrientations[1];
        int it = frame % (rightOrientation.size() * DESACCELERATING_RATE);
		currentClip = &this->rightOrientation[it / DESACCELERATING_RATE];
        
	} else if(orientation == LEFT)  {
        headClip = &this->headOrientations[2];
        int it = frame % (leftOrientation.size() * DESACCELERATING_RATE);
        currentClip = &this->leftOrientation[it / DESACCELERATING_RATE];
	
    } else if(orientation == UP)  {
        headClip = &this->headOrientations[3];
        int it = frame % (backOrientation.size() * DESACCELERATING_RATE);
		currentClip = &this->backOrientation[it / DESACCELERATING_RATE];
	
    } else if(orientation == DOWN)  {
        headClip = &this->headOrientations[0];
        int it = frame % (frontOrientation.size() * DESACCELERATING_RATE);
		currentClip = &this->frontOrientation[it / DESACCELERATING_RATE];

	} else {
        headClip = &this->headOrientations[0];
		currentClip = &this->frontOrientation[0];
    }

    this->headTexture.render(bodyPosX+3, bodyPosY-17, gRenderer, headClip);
    this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);
}


void Ghost::set_sprites() {
    this->load_head_sprite();
    this->load_front_walking_sprite();
    this->load_back_walking_sprite();
    this->load_left_walking_sprite();
    this->load_right_walking_sprite();
}


void Ghost::load_head_sprite() {
    SDL_Rect front = {0, 0, 17, 16};
    this->headOrientations.push_back(front);

    SDL_Rect right = {17, 0, 17, 16};
    this->headOrientations.push_back(right);

    SDL_Rect left = {34, 0, 17, 16};
    this->headOrientations.push_back(left);

    SDL_Rect back = {51, 0, 17, 16};
    this->headOrientations.push_back(back);
}

void Ghost::load_front_walking_sprite() {
    SDL_Rect first = {2, 0, 25, 30};
    this->frontOrientation.push_back(first);

    SDL_Rect second = {31, 0, 25, 30};
    this->frontOrientation.push_back(second);

    SDL_Rect third = {60, 0, 25, 30};
    this->frontOrientation.push_back(third);
}

void Ghost::load_back_walking_sprite() {
    SDL_Rect first = {2, 32, 25, 30};
    this->backOrientation.push_back(first);

    SDL_Rect second = {31, 32, 25, 30};
    this->backOrientation.push_back(second);

    SDL_Rect third = {60, 32, 25, 30};
    this->backOrientation.push_back(third);
}

void Ghost::load_left_walking_sprite() {
    SDL_Rect first = {5, 65, 25, 30};
    this->leftOrientation.push_back(first);

    SDL_Rect second = {34, 65, 25, 30};
    this->leftOrientation.push_back(second);

    SDL_Rect third = {63, 65, 25, 30};
    this->leftOrientation.push_back(third);
}


void Ghost::load_right_walking_sprite() {
    SDL_Rect first = {0, 97, 25, 30};
    this->rightOrientation.push_back(first);

    SDL_Rect second = {27, 97, 25, 30};
    this->rightOrientation.push_back(second);

    SDL_Rect third = {57, 97, 25, 30};
    this->rightOrientation.push_back(third);
}
