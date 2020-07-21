
#include <iostream>

#include "client_weapon.h"
#include "client_player.h"



Weapon::Weapon(int offset) : offset(offset) {}

Weapon::~Weapon() {
	std::cout << "DESTRUYENDO WEAPON" << std::endl;
	// weaponTexture.free();
}


void Weapon::render(int &bodyPosX, int &bodyPosY, SDL_Renderer* gRenderer, int &orientation, int &frame) {
	//Show Character
	if (orientation == RIGHT) {
		int it = frame % (walkingRightPlayer.size() * DESACCELERATING_RATE);
		SDL_Rect* currentClip = &this->walkingRightPlayer[it / DESACCELERATING_RATE];
		this->weaponTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);
        
	} else if(orientation == LEFT)  {
		int it = frame % (walkingLeftPlayer.size() * DESACCELERATING_RATE);
		SDL_Rect* currentClip = &this->walkingLeftPlayer[it / DESACCELERATING_RATE];
		this->weaponTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);
	
    } else if(orientation == UP)  {
		int it = frame % (walkingBackPlayer.size() * DESACCELERATING_RATE);
		SDL_Rect* currentClip = &this->walkingBackPlayer[it / DESACCELERATING_RATE];
		this->weaponTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);
	
    } else if(orientation == DOWN)  {
		int it = frame % (walkingFrontPlayer.size() * DESACCELERATING_RATE);
		SDL_Rect* currentClip = &this->walkingFrontPlayer[it / DESACCELERATING_RATE];
		this->weaponTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);

	} else {
		SDL_Rect* currentClip = &this->walkingFrontPlayer[0];
		this->weaponTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);
    }
}

int Weapon::get_id() {
	return id;
}
