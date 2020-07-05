
#include "client_weapon.h"
#include "client_player.h"



Weapon::Weapon(int offset) : offset(offset) {}

Weapon::~Weapon() {}


void Weapon::render(int &bodyPosX, int &bodyPosY, SDL_Renderer* gRenderer, int &orientation, int &frame) {
	//Show Character
	if (orientation == RIGHT) {
		SDL_Rect* currentClip = &this->walkingRightPlayer[ frame % walkingRightPlayer.size() ];
		this->weaponTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);
        
	} else if(orientation == LEFT)  {
		SDL_Rect* currentClip = &this->walkingLeftPlayer[ frame % walkingLeftPlayer.size() ];
		this->weaponTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);
	
    } else if(orientation == UP)  {
		SDL_Rect* currentClip = &this->walkingBackPlayer[ frame % walkingBackPlayer.size() ];
		this->weaponTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);
	
    } else if(orientation == DOWN)  {
		SDL_Rect* currentClip = &this->walkingFrontPlayer[ frame % walkingFrontPlayer.size() ];
		this->weaponTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);

	} else {
		SDL_Rect* currentClip = &this->walkingFrontPlayer[ 0 ];
		this->weaponTexture.render(bodyPosX, bodyPosY+offset, gRenderer, currentClip);
    }
}

int Weapon::get_id() {
	return id;
}
