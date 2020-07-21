#include "client_helmet.h"
#include "client_player.h"


Helmet::Helmet(int offset) : offset(offset) {}

Helmet::~Helmet() {
	// helmetTexture.free();
}

void Helmet::render(int &headPosX, int &headPosY, SDL_Renderer* gRenderer, int &orientation, int &frame) {
	//Show Character
	if (orientation == RIGHT) {
		SDL_Rect* headClip = &this->helmetOrientation[1];
		this->helmetTexture.render(headPosX-1, headPosY+offset, gRenderer, headClip);
        
	} else if(orientation == LEFT)  {
		SDL_Rect* headClip = &this->helmetOrientation[2];
		this->helmetTexture.render(headPosX-1, headPosY+offset, gRenderer, headClip);
	
    } else if(orientation == UP)  {
		SDL_Rect* headClip = &this->helmetOrientation[3];
		this->helmetTexture.render(headPosX-1, headPosY+offset, gRenderer, headClip);
	
    } else if(orientation == DOWN)  {
		SDL_Rect* headClip = &this->helmetOrientation[0];
		this->helmetTexture.render(headPosX-1, headPosY+offset, gRenderer, headClip);

	} else {
		SDL_Rect* headClip = &this->helmetOrientation[0];
		this->helmetTexture.render(headPosX-1, headPosY+offset, gRenderer, headClip);
    }
}

int Helmet::get_id() {
	return id;
}
