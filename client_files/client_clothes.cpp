
#include <iostream>

#include "client_clothes.h"
#include "client_player.h"


Clothes::Clothes(int width, int height) : width(width), height(height) {}



void Clothes::render(int &bodyPosX, int &bodyPosY, SDL_Renderer* gRenderer, int &orientation, int &frame) {
    // Show Character
    if (orientation == RIGHT) {
		int it = frame % (walkingRightPlayer.size() * DESACCELERATING_RATE);
		SDL_Rect* currentClip = &this->walkingRightPlayer[it / DESACCELERATING_RATE];
		this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);
        
	} else if(orientation == LEFT)  {
		int it = frame % (walkingLeftPlayer.size() * DESACCELERATING_RATE);
		SDL_Rect *currentClip = &this->walkingLeftPlayer[it / DESACCELERATING_RATE];
		this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);
	
    } else if(orientation == UP)  {
		int it = frame % (walkingBackPlayer.size() * DESACCELERATING_RATE);
		SDL_Rect *currentClip = &this->walkingBackPlayer[it / DESACCELERATING_RATE];
		this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);
	
    } else if(orientation == DOWN)  {
		int it = frame % (walkingFrontPlayer.size() * DESACCELERATING_RATE);
		SDL_Rect *currentClip = &this->walkingFrontPlayer[it / DESACCELERATING_RATE];
		this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);

	} else {
		SDL_Rect* currentClip = &this->walkingFrontPlayer[0];
		this->bodyTexture.render( bodyPosX, bodyPosY, gRenderer, currentClip);
    }
}


Clothes::~Clothes() {
	std::cout << "DESTROYING CLOTHES" << std::endl;
	bodyTexture.free();
}


int Clothes::get_id() {
	return id;
}

void Clothes::set_short_sprites() {
    this->load_front_walking_sprite();
    this->load_left_walking_sprite();
    this->load_right_walking_sprite();
    this->load_back_walking_sprite();
}



void Clothes::set_tall_sprites() {
    loadTallWalkingFrontSprite();
    loadTallWalkingBackSprite();
    loadTallWalkingLeftSprite();
    loadTallWalkingRightSprite();
}


void Clothes::load_front_walking_sprite() {
	SDL_Rect first = {2, 13, width, height};
	this->walkingFrontPlayer.push_back(first);

	SDL_Rect second = {27, 13, width, height};
	this->walkingFrontPlayer.push_back(second);

	SDL_Rect third = {52, 13, width, height};
	this->walkingFrontPlayer.push_back(third);

	SDL_Rect fourth = {77, 13, width, height};
	this->walkingFrontPlayer.push_back(fourth);

	SDL_Rect fifth = {102, 13, width, height};
	this->walkingFrontPlayer.push_back(fifth);

	SDL_Rect sixth = {127, 13, width, height};
	this->walkingFrontPlayer.push_back(sixth);
}


void Clothes::load_back_walking_sprite() {
	SDL_Rect first = {2, 58, width, height};
	this->walkingBackPlayer.push_back(first);

	SDL_Rect second = {27, 58, width, height};
	this->walkingBackPlayer.push_back(second);

	SDL_Rect third = {52, 58, width, height};
	this->walkingBackPlayer.push_back(third);

	SDL_Rect fourth = {77, 58, width, height};
	this->walkingBackPlayer.push_back(fourth);

	SDL_Rect fifth = {102, 58, width, height};
	this->walkingBackPlayer.push_back(fifth);

	SDL_Rect sixth = {127, 58, width, height};
	this->walkingBackPlayer.push_back(sixth);
}


void Clothes::load_left_walking_sprite() {
	SDL_Rect first = {2, 103, width, height};
	this->walkingLeftPlayer.push_back(first);

	SDL_Rect second = {27, 103, width, height};
	this->walkingLeftPlayer.push_back(second);

	SDL_Rect third = {52, 103, width, height};
	this->walkingLeftPlayer.push_back(third);

	SDL_Rect fourth = {77, 103, width, height};
	this->walkingLeftPlayer.push_back(fourth);

	SDL_Rect fifth = {102, 103, width, height};
	this->walkingLeftPlayer.push_back(fifth);
}


void Clothes::load_right_walking_sprite() {
	SDL_Rect first = {2, 148, width, height};
	this->walkingRightPlayer.push_back(first);

	SDL_Rect second = {27, 148, width, height};
	this->walkingRightPlayer.push_back(second);

	SDL_Rect third = {52, 148, width, height};
	this->walkingRightPlayer.push_back(third);

	SDL_Rect fourth = {77, 148, width, height};
	this->walkingRightPlayer.push_back(fourth);

	SDL_Rect fifth = {102, 148, width, height};
	this->walkingRightPlayer.push_back(fifth);
}


void Clothes::loadTallWalkingFrontSprite() {
	SDL_Rect first = {1, 2, width, height};
	this->walkingFrontPlayer.push_back(first);

	SDL_Rect second = {26, 2, width, height};
	this->walkingFrontPlayer.push_back(second);

	SDL_Rect third = {51, 2, width, height};
	this->walkingFrontPlayer.push_back(third);

	SDL_Rect fourth = {76, 2, width, height};
	this->walkingFrontPlayer.push_back(fourth);

	SDL_Rect fifth = {101, 2, width, height};
	this->walkingFrontPlayer.push_back(fifth);

	SDL_Rect sixth = {126, 2, width, height};
	this->walkingFrontPlayer.push_back(sixth);
}



void Clothes::loadTallWalkingBackSprite() {
	SDL_Rect first = {1, 48, width, height};
	this->walkingBackPlayer.push_back(first);

	SDL_Rect second = {26, 48, width, height};
	this->walkingBackPlayer.push_back(second);

	SDL_Rect third = {51, 48, width, height};
	this->walkingBackPlayer.push_back(third);

	SDL_Rect fourth = {76, 48, width, height};
	this->walkingBackPlayer.push_back(fourth);

	SDL_Rect fifth = {101, 48, width, height};
	this->walkingBackPlayer.push_back(fifth);

	SDL_Rect sixth = {126, 48, width, height};
	this->walkingBackPlayer.push_back(sixth);
}


void Clothes::loadTallWalkingLeftSprite() {

	SDL_Rect first = {1, 93, width, height};
	this->walkingLeftPlayer.push_back(first);

	SDL_Rect second = {23, 93, width, height};
	this->walkingLeftPlayer.push_back(second);

	SDL_Rect third = {49, 93, width, height};
	this->walkingLeftPlayer.push_back(third);

	SDL_Rect fourth = {74, 93, width, height};
	this->walkingLeftPlayer.push_back(fourth);

	SDL_Rect fifth = {99, 93, width, height};
	this->walkingLeftPlayer.push_back(fifth);
}


void Clothes::loadTallWalkingRightSprite() {
	SDL_Rect first = {1, 138, width, height};
	this->walkingRightPlayer.push_back(first);

	SDL_Rect second = {29, 138, width, height};
	this->walkingRightPlayer.push_back(second);

	SDL_Rect third = {54, 138, width, height};
	this->walkingRightPlayer.push_back(third);

	SDL_Rect fourth = {78, 138, width, height};
	this->walkingRightPlayer.push_back(fourth);

	SDL_Rect fifth = {103, 138, width, height};
	this->walkingRightPlayer.push_back(fifth);
}
