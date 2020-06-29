
#include "client_player.h"
#include "client_player_picture.h"


/**
 * PlayerPicture
 */

PlayerPicture::PlayerPicture(SDL_Renderer* gRenderer, const char* head_path) {

    this->load_pictures(gRenderer, head_path); 

}



bool PlayerPicture::load_pictures(SDL_Renderer* gRenderer, const char* head_path) {
    if( !this->headTexture.loadFromFile( head_path, gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

    this->set_head_sprite();
    return true;
}


void PlayerPicture::set_head_sprite() {
    this->headOrientations[0].x = 1;
	this->headOrientations[0].y = 0;
	this->headOrientations[0].w= 15;
	this->headOrientations[0].h= 20;

	this->headOrientations[1].x = 18;
	this->headOrientations[1].y = 0;
	this->headOrientations[1].w= 15;
	this->headOrientations[1].h= 20;

	this->headOrientations[2].x = 36;
	this->headOrientations[2].y = 0;
	this->headOrientations[2].w= 15;
	this->headOrientations[2].h= 20;

	this->headOrientations[3].x = 52;
	this->headOrientations[3].y = 0;
	this->headOrientations[3].w= 15;
	this->headOrientations[3].h= 20;
}


void PlayerPicture::set_clothes(Clothes* clothes) {
    this->clothes = clothes;
}




void PlayerPicture::render(int &bodyPosX, int &bodyPosY, int &headPosX, int &headPosY, SDL_Renderer* gRenderer, int &orientation, int &frame) {
    
	//Show Character
	if (orientation == RIGHT) {
		SDL_Rect* headClip = &this->headOrientations[1];
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);
        
	} else if(orientation == LEFT)  {
		SDL_Rect* headClip = &this->headOrientations[2];
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);
	
    } else if(orientation == UP)  {
		SDL_Rect* headClip = &this->headOrientations[3];
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);
	
    } else if(orientation == DOWN)  {
		SDL_Rect* headClip = &this->headOrientations[0];
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);

	} else {
		SDL_Rect* headClip = &this->headOrientations[0];
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);
    }

    this->clothes->render(bodyPosX, bodyPosY, gRenderer, orientation, frame);
}




EquippedPlayer::EquippedPlayer(PlayerPicture* player) {
	this->player = player;
	this->helmet = NULL;
	this->weapon = NULL;
}



void EquippedPlayer::setHelmet(Helmet* helmet) {
	this->helmet = helmet;
}


void EquippedPlayer::setWeapon(Weapon* weapon) {
	this->weapon = weapon;
}


void EquippedPlayer::render(
	int &bodyPosX, 
	int &bodyPosY,int &headPosX, int &headPosY, SDL_Renderer* gRenderer, int &orientation, int &frame) {

	player->render(bodyPosX, bodyPosY, headPosX, headPosY, gRenderer, orientation, frame);
	
	if (helmet != NULL)
		helmet->render(headPosX, headPosY, gRenderer, orientation, frame);
		
	if (weapon != NULL)
		weapon->render(bodyPosX, bodyPosY, gRenderer, orientation, frame);
			
}
