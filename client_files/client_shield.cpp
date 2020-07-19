#include <iostream>
#include "client_shield.h"
#include "client_player.h"



Shield::Shield(int offset) : offset(offset) {}

Shield::~Shield() {
	std::cout << "Destruyendo SHIELD" << std::endl;
	shieldTexture.free();
}


void Shield::render(int &bodyPosX, int &bodyPosY, SDL_Renderer* gRenderer, int &orientation, int &frame) {
	//Show Character
	if (orientation == RIGHT) {
		SDL_Rect* currentClip = &this->walkingRightPlayer[ frame % walkingRightPlayer.size() ];
		this->shieldTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);
        
	} else if(orientation == LEFT)  {
		SDL_Rect* currentClip = &this->walkingLeftPlayer[ frame % walkingLeftPlayer.size() ];
		this->shieldTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);
	
    } else if(orientation == UP)  {
		SDL_Rect* currentClip = &this->walkingBackPlayer[ frame % walkingBackPlayer.size() ];
		this->shieldTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);
	
    } else if(orientation == DOWN)  {
		SDL_Rect* currentClip = &this->walkingFrontPlayer[ frame % walkingFrontPlayer.size() ];
		this->shieldTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);

	} else {
		SDL_Rect* currentClip = &this->walkingFrontPlayer[ 0 ];
		this->shieldTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);
    }
}

int Shield::get_id() {
	return id;
}
