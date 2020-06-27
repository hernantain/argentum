
#include "client_clothes.h"
#include "client_player.h"


Clothes::Clothes(int width, int height) : width(width), height(height) {}



void Clothes::render(int &bodyPosX, int &bodyPosY, SDL_Renderer* gRenderer, int &orientation, int &frame) {
    // Show Character

    if (orientation == RIGHT) {
		SDL_Rect* currentClip = &this->walkingRightPlayer[ frame / 5 ];
		this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);
        
	} else if(orientation == LEFT)  {
		SDL_Rect *currentClip = &this->walkingLeftPlayer[ frame / 5 ];
		this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);
	
    } else if(orientation == UP)  {
		SDL_Rect *currentClip = &this->walkingBackPlayer[ frame / 5 ];
		this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);
	
    } else if(orientation == DOWN)  {
		SDL_Rect *currentClip = &this->walkingFrontPlayer[ frame / 5 ];
		this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);

	} else {
		SDL_Rect* currentClip = &this->walkingFrontPlayer[0];
		this->bodyTexture.render( bodyPosX, bodyPosY, gRenderer, currentClip);
    }
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
	this->walkingFrontPlayer[0].x = 2;
	this->walkingFrontPlayer[0].y = 13;
	this->walkingFrontPlayer[0].w = width;
	this->walkingFrontPlayer[0].h = height;

	this->walkingFrontPlayer[1].x = 27;
	this->walkingFrontPlayer[1].y = 13;
	this->walkingFrontPlayer[1].w = width;
	this->walkingFrontPlayer[1].h = height;

	this->walkingFrontPlayer[2].x = 52;
	this->walkingFrontPlayer[2].y = 13;
	this->walkingFrontPlayer[2].w = width;
	this->walkingFrontPlayer[2].h = height;

	this->walkingFrontPlayer[3].x = 77;
	this->walkingFrontPlayer[3].y = 13;
	this->walkingFrontPlayer[3].w = width;
	this->walkingFrontPlayer[3].h = height;

	this->walkingFrontPlayer[4].x = 102;
	this->walkingFrontPlayer[4].y = 13;
	this->walkingFrontPlayer[4].w = width;
	this->walkingFrontPlayer[4].h = height;

	this->walkingFrontPlayer[5].x = 127;
	this->walkingFrontPlayer[5].y = 13;
	this->walkingFrontPlayer[5].w = width;
	this->walkingFrontPlayer[5].h = height;
}


void Clothes::load_back_walking_sprite() {
	this->walkingBackPlayer[0].x = 2;
	this->walkingBackPlayer[0].y = 58;
	this->walkingBackPlayer[0].w = width;
	this->walkingBackPlayer[0].h = height;

	this->walkingBackPlayer[1].x = 27;
	this->walkingBackPlayer[1].y = 58;
	this->walkingBackPlayer[1].w = width;
	this->walkingBackPlayer[1].h = height;

	this->walkingBackPlayer[2].x = 52;
	this->walkingBackPlayer[2].y = 58;
	this->walkingBackPlayer[2].w = width;
	this->walkingBackPlayer[2].h = height;

	this->walkingBackPlayer[3].x = 77;
	this->walkingBackPlayer[3].y = 58;
	this->walkingBackPlayer[3].w = width;
	this->walkingBackPlayer[3].h = height;

	this->walkingBackPlayer[4].x = 102;
	this->walkingBackPlayer[4].y = 58;
	this->walkingBackPlayer[4].w = width;
	this->walkingBackPlayer[4].h = height;

	this->walkingBackPlayer[5].x = 127;
	this->walkingBackPlayer[5].y = 58;
	this->walkingBackPlayer[5].w = width;
	this->walkingBackPlayer[5].h = height;
}


void Clothes::load_left_walking_sprite() {
	this->walkingLeftPlayer[0].x = 2;
	this->walkingLeftPlayer[0].y = 103;
	this->walkingLeftPlayer[0].w = width;
	this->walkingLeftPlayer[0].h = height;

	this->walkingLeftPlayer[1].x = 27;
	this->walkingLeftPlayer[1].y = 103;
	this->walkingLeftPlayer[1].w = width;
	this->walkingLeftPlayer[1].h = height;

	this->walkingLeftPlayer[2].x = 52;
	this->walkingLeftPlayer[2].y = 103;
	this->walkingLeftPlayer[2].w = width;
	this->walkingLeftPlayer[2].h = height;

	this->walkingLeftPlayer[3].x = 77;
	this->walkingLeftPlayer[3].y = 103;
	this->walkingLeftPlayer[3].w = width;
	this->walkingLeftPlayer[3].h = height;

	this->walkingLeftPlayer[4].x = 102;
	this->walkingLeftPlayer[4].y = 103;
	this->walkingLeftPlayer[4].w = width;
	this->walkingLeftPlayer[4].h = height;
}


void Clothes::load_right_walking_sprite() {
	this->walkingRightPlayer[0].x = 2;
	this->walkingRightPlayer[0].y = 148;
	this->walkingRightPlayer[0].w = width;
	this->walkingRightPlayer[0].h = height;

	this->walkingRightPlayer[1].x = 27;
	this->walkingRightPlayer[1].y = 148;
	this->walkingRightPlayer[1].w = width;
	this->walkingRightPlayer[1].h = height;

	this->walkingRightPlayer[2].x = 52;
	this->walkingRightPlayer[2].y = 148;
	this->walkingRightPlayer[2].w = width;
	this->walkingRightPlayer[2].h = height;

	this->walkingRightPlayer[3].x = 77;
	this->walkingRightPlayer[3].y = 148;
	this->walkingRightPlayer[3].w = width;
	this->walkingRightPlayer[3].h = height;

	this->walkingRightPlayer[4].x = 102;
	this->walkingRightPlayer[4].y = 148;
	this->walkingRightPlayer[4].w = width;
	this->walkingRightPlayer[4].h = height;
}


void Clothes::loadTallWalkingFrontSprite() {
	this->walkingFrontPlayer[0].x = 1;
	this->walkingFrontPlayer[0].y = 2;
	this->walkingFrontPlayer[0].w  = width;
	this->walkingFrontPlayer[0].h  = height;

	this->walkingFrontPlayer[1].x = 26;
	this->walkingFrontPlayer[1].y = 2;
	this->walkingFrontPlayer[1].w  = width;
	this->walkingFrontPlayer[1].h  = height;

	this->walkingFrontPlayer[2].x = 51;
	this->walkingFrontPlayer[2].y = 2;
	this->walkingFrontPlayer[2].w  = width;
	this->walkingFrontPlayer[2].h  = height;

	this->walkingFrontPlayer[3].x = 76;
	this->walkingFrontPlayer[3].y = 2;
	this->walkingFrontPlayer[3].w  = width;
	this->walkingFrontPlayer[3].h  = height;

	this->walkingFrontPlayer[4].x = 101;
	this->walkingFrontPlayer[4].y = 2;
	this->walkingFrontPlayer[4].w  = width;
	this->walkingFrontPlayer[4].h  = height;

	this->walkingFrontPlayer[5].x = 126;
	this->walkingFrontPlayer[5].y = 2;
	this->walkingFrontPlayer[5].w  = width;
	this->walkingFrontPlayer[5].h  = height;
}



void Clothes::loadTallWalkingBackSprite() {
	this->walkingBackPlayer[0].x = 1;
	this->walkingBackPlayer[0].y = 48;
	this->walkingBackPlayer[0].w  = width;
	this->walkingBackPlayer[0].h  = height;

	this->walkingBackPlayer[1].x = 26;
	this->walkingBackPlayer[1].y = 48;
	this->walkingBackPlayer[1].w  = width;
	this->walkingBackPlayer[1].h  = height;

	this->walkingBackPlayer[2].x = 51;
	this->walkingBackPlayer[2].y = 48;
	this->walkingBackPlayer[2].w  = width;
	this->walkingBackPlayer[2].h  = height;

	this->walkingBackPlayer[3].x = 76;
	this->walkingBackPlayer[3].y = 48;
	this->walkingBackPlayer[3].w  = width;
	this->walkingBackPlayer[3].h  = height;

	this->walkingBackPlayer[4].x = 101;
	this->walkingBackPlayer[4].y = 48;
	this->walkingBackPlayer[4].w  = width;
	this->walkingBackPlayer[4].h  = height;

	this->walkingBackPlayer[5].x = 126;
	this->walkingBackPlayer[5].y = 48;
	this->walkingBackPlayer[5].w  = width;
	this->walkingBackPlayer[5].h  = height;
}


void Clothes::loadTallWalkingLeftSprite() {
	this->walkingLeftPlayer[0].x = 1;
	this->walkingLeftPlayer[0].y = 93;
	this->walkingLeftPlayer[0].w  = width;
	this->walkingLeftPlayer[0].h  = height;

	this->walkingLeftPlayer[1].x = 23;
	this->walkingLeftPlayer[1].y = 93;
	this->walkingLeftPlayer[1].w  = width;
	this->walkingLeftPlayer[1].h  = height;

	this->walkingLeftPlayer[2].x = 49;
	this->walkingLeftPlayer[2].y = 93;
	this->walkingLeftPlayer[2].w  = width;
	this->walkingLeftPlayer[2].h  = height;

	this->walkingLeftPlayer[3].x = 74;
	this->walkingLeftPlayer[3].y = 93;
	this->walkingLeftPlayer[3].w  = width;
	this->walkingLeftPlayer[3].h  = height;

	this->walkingLeftPlayer[4].x = 99;
	this->walkingLeftPlayer[4].y = 93;
	this->walkingLeftPlayer[4].w  = width;
	this->walkingLeftPlayer[4].h  = height;
}


void Clothes::loadTallWalkingRightSprite() {
	this->walkingRightPlayer[0].x = 1;
	this->walkingRightPlayer[0].y = 138;
	this->walkingRightPlayer[0].w  = width;
	this->walkingRightPlayer[0].h  = height;

	this->walkingRightPlayer[1].x = 29;
	this->walkingRightPlayer[1].y = 138;
	this->walkingRightPlayer[1].w  = width;
	this->walkingRightPlayer[1].h  = height;

	this->walkingRightPlayer[2].x = 54;
	this->walkingRightPlayer[2].y = 138;
	this->walkingRightPlayer[2].w  = width;
	this->walkingRightPlayer[2].h  = height;

	this->walkingRightPlayer[3].x = 78;
	this->walkingRightPlayer[3].y = 138;
	this->walkingRightPlayer[3].w  = width;
	this->walkingRightPlayer[3].h  = height;

	this->walkingRightPlayer[4].x = 103;
	this->walkingRightPlayer[4].y = 138;
	this->walkingRightPlayer[4].w  = width;
	this->walkingRightPlayer[4].h  = height;
}
