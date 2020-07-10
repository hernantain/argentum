
#include "client_skeleton.h"


Skeleton::Skeleton(SDL_Renderer* gRenderer) : NpcPicture(gRenderer) {
    if (this->load_pictures("images/esqueleto.png"))
        this->set_sprites();
}



void Skeleton::set_sprites() {
    this->load_front_walking_sprite();  
    this->load_back_walking_sprite();
    this->load_left_walking_sprite();
    this->load_right_walking_sprite();
}


void Skeleton::render(int posX, int posY, SDL_Renderer* gRenderer, int &orientation, int &frame) {
    // Show skeleton
    if (orientation == RIGHT) {
		SDL_Rect* currentClip = &this->rightOrientation[ frame % 5 ];
		this->npcTexture.render(posX, posY, gRenderer, currentClip);
        
	} else if(orientation == LEFT)  {
		SDL_Rect *currentClip = &this->leftOrientation[ frame % 5 ];
		this->npcTexture.render(posX, posY, gRenderer, currentClip);
	
    } else if(orientation == UP)  {
		SDL_Rect *currentClip = &this->backOrientation[ frame % 5 ];
		this->npcTexture.render(posX, posY, gRenderer, currentClip);
	
    } else if(orientation == DOWN)  {
		SDL_Rect *currentClip = &this->frontOrientation[ frame % 5 ];
		this->npcTexture.render(posX, posY, gRenderer, currentClip);

	} else {
		SDL_Rect* currentClip = &this->frontOrientation[0];
		this->npcTexture.render( posX, posY, gRenderer, currentClip);
    }
}


void Skeleton::load_front_walking_sprite() {
    this->frontOrientation[0].x = 2;
    this->frontOrientation[0].y = 3;
    this->frontOrientation[0].w = 21;
    this->frontOrientation[0].h = 50;

    this->frontOrientation[1].x = 27;
    this->frontOrientation[1].y = 3;
    this->frontOrientation[1].w = 21;
    this->frontOrientation[1].h = 50;

    this->frontOrientation[2].x = 52;
    this->frontOrientation[2].y = 3;
    this->frontOrientation[2].w = 21;
    this->frontOrientation[2].h = 50;

    this->frontOrientation[3].x = 76;
    this->frontOrientation[3].y = 3;
    this->frontOrientation[3].w = 21;
    this->frontOrientation[3].h = 50;

    this->frontOrientation[4].x = 102;
    this->frontOrientation[4].y = 3;
    this->frontOrientation[4].w = 21;
    this->frontOrientation[4].h = 50;

    this->frontOrientation[5].x = 126;
    this->frontOrientation[5].y = 3;
    this->frontOrientation[5].w = 21;
    this->frontOrientation[5].h = 50;
}


void Skeleton::load_back_walking_sprite() {
    this->backOrientation[0].x = 2;
    this->backOrientation[0].y = 54;
    this->backOrientation[0].w = 21;
    this->backOrientation[0].h = 50;

    this->backOrientation[1].x = 27;
    this->backOrientation[1].y = 54;
    this->backOrientation[1].w = 21;
    this->backOrientation[1].h = 50;

    this->backOrientation[2].x = 52;
    this->backOrientation[2].y = 54;
    this->backOrientation[2].w = 21;
    this->backOrientation[2].h = 50;

    this->backOrientation[3].x = 76;
    this->backOrientation[3].y = 54;
    this->backOrientation[3].w = 21;
    this->backOrientation[3].h = 50;

    this->backOrientation[4].x = 102;
    this->backOrientation[4].y = 54;
    this->backOrientation[4].w = 21;
    this->backOrientation[4].h = 50;

    this->backOrientation[5].x = 126;
    this->backOrientation[5].y = 54;
    this->backOrientation[5].w = 21;
    this->backOrientation[5].h = 50;
}


void Skeleton::load_left_walking_sprite() {
    this->leftOrientation[0].x = 2;
    this->leftOrientation[0].y = 106;
    this->leftOrientation[0].w = 21;
    this->leftOrientation[0].h = 50;

    this->leftOrientation[1].x = 27;
    this->leftOrientation[1].y = 106;
    this->leftOrientation[1].w = 21;
    this->leftOrientation[1].h = 50;

    this->leftOrientation[2].x = 52;
    this->leftOrientation[2].y = 106;
    this->leftOrientation[2].w = 21;
    this->leftOrientation[2].h = 50;

    this->leftOrientation[3].x = 76;
    this->leftOrientation[3].y = 106;
    this->leftOrientation[3].w = 21;
    this->leftOrientation[3].h = 50;

    this->leftOrientation[4].x = 102;
    this->leftOrientation[4].y = 106;
    this->leftOrientation[4].w = 21;
    this->leftOrientation[4].h = 50;
}


void Skeleton::load_right_walking_sprite() {
    this->rightOrientation[0].x = 2;
    this->rightOrientation[0].y = 158;
    this->rightOrientation[0].w = 21;
    this->rightOrientation[0].h = 50;

    this->rightOrientation[1].x = 27;
    this->rightOrientation[1].y = 158;
    this->rightOrientation[1].w = 21;
    this->rightOrientation[1].h = 50;

    this->rightOrientation[2].x = 52;
    this->rightOrientation[2].y = 158;
    this->rightOrientation[2].w = 21;
    this->rightOrientation[2].h = 50;

    this->rightOrientation[3].x = 76;
    this->rightOrientation[3].y = 158;
    this->rightOrientation[3].w = 21;
    this->rightOrientation[3].h = 50;

    this->rightOrientation[4].x = 102;
    this->rightOrientation[4].y = 158;
    this->rightOrientation[4].w = 21;
    this->rightOrientation[4].h = 50;
}
