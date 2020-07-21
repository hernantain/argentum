#include <iostream>
#include "client_shield.h"
#include "client_player.h"



Shield::Shield(int offset) : offset(offset) {}

Shield::~Shield() {
	std::cout << "Destruyendo SHIELD" << std::endl;
	// shieldTexture.free();
}


void Shield::render(int &bodyPosX, int &bodyPosY, SDL_Renderer* gRenderer, int &orientation, int &frame) {
	//Show Character
	if (orientation == RIGHT) {
		int it = frame % (walkingRightPlayer.size() * DESACCELERATING_RATE);
		SDL_Rect* currentClip = &this->walkingRightPlayer[it / DESACCELERATING_RATE];
		this->shieldTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);
        
	} else if(orientation == LEFT)  {
		int it = frame % (walkingLeftPlayer.size() * DESACCELERATING_RATE);
		SDL_Rect* currentClip = &this->walkingLeftPlayer[it / DESACCELERATING_RATE];
		this->shieldTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);
	
    } else if(orientation == UP)  {
		int it = frame % (walkingBackPlayer.size() * DESACCELERATING_RATE);
		SDL_Rect* currentClip = &this->walkingBackPlayer[it / DESACCELERATING_RATE];
		this->shieldTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);
	
    } else if(orientation == DOWN)  {
		int it = frame % (walkingFrontPlayer.size() * DESACCELERATING_RATE);
		SDL_Rect* currentClip = &this->walkingFrontPlayer[it / DESACCELERATING_RATE];
		this->shieldTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);

	} else {
		SDL_Rect* currentClip = &this->walkingFrontPlayer[0];
		this->shieldTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);
    }
}

int Shield::get_id() {
	return id;
}
