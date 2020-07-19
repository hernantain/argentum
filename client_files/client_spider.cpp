

#include "client_spider.h"


Spider::Spider(SDL_Renderer* gRenderer) : NpcPicture(gRenderer) {
    if (this->load_pictures("images/arana3.png"))
        this->set_sprites();
}

Spider::~Spider() {}

void Spider::set_sprites() {
    this->load_front_walking_sprite();  
    this->load_back_walking_sprite();
    this->load_left_walking_sprite();
    this->load_right_walking_sprite();
}


void Spider::render(int posX, int posY, SDL_Renderer* gRenderer, int &orientation, int &frame) {
    // Show Character

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


void Spider::load_front_walking_sprite() {
    this->frontOrientation[0].x = 1;
    this->frontOrientation[0].y = 0;
    this->frontOrientation[0].w = 52;
    this->frontOrientation[0].h = 35;

    this->frontOrientation[1].x = 55;
    this->frontOrientation[1].y = 0;
    this->frontOrientation[1].w = 52;
    this->frontOrientation[1].h = 35;

    this->frontOrientation[2].x = 106;
    this->frontOrientation[2].y = 0;
    this->frontOrientation[2].w = 52;
    this->frontOrientation[2].h = 35;

    this->frontOrientation[3].x = 160;
    this->frontOrientation[3].y = 0;
    this->frontOrientation[3].w = 52;
    this->frontOrientation[3].h = 35;
}

void Spider::load_back_walking_sprite() {
    this->backOrientation[0].x = 1;
    this->backOrientation[0].y = 35;
    this->backOrientation[0].w = 52;
    this->backOrientation[0].h = 35;

    this->backOrientation[1].x = 55;
    this->backOrientation[1].y = 35;
    this->backOrientation[1].w = 52;
    this->backOrientation[1].h = 35;

    this->backOrientation[2].x = 106;
    this->backOrientation[2].y = 35;
    this->backOrientation[2].w = 52;
    this->backOrientation[2].h = 35;

    this->backOrientation[3].x = 160;
    this->backOrientation[3].y = 35;
    this->backOrientation[3].w = 52;
    this->backOrientation[3].h = 35;
}

void Spider::load_left_walking_sprite() {
    this->leftOrientation[0].x = 1;
    this->leftOrientation[0].y = 70;
    this->leftOrientation[0].w = 52;
    this->leftOrientation[0].h = 35;

    this->leftOrientation[1].x = 55;
    this->leftOrientation[1].y = 70;
    this->leftOrientation[1].w = 52;
    this->leftOrientation[1].h = 35;

    this->leftOrientation[2].x = 106;
    this->leftOrientation[2].y = 70;
    this->leftOrientation[2].w = 52;
    this->leftOrientation[2].h = 35;

    this->leftOrientation[3].x = 160;
    this->leftOrientation[3].y = 70;
    this->leftOrientation[3].w = 52;
    this->leftOrientation[3].h = 35;
}

void Spider::load_right_walking_sprite() {
    this->rightOrientation[0].x = 1;
    this->rightOrientation[0].y = 105;
    this->rightOrientation[0].w = 52;
    this->rightOrientation[0].h = 35;

    this->rightOrientation[1].x = 55;
    this->rightOrientation[1].y = 105;
    this->rightOrientation[1].w = 52;
    this->rightOrientation[1].h = 35;

    this->rightOrientation[2].x = 106;
    this->rightOrientation[2].y = 105;
    this->rightOrientation[2].w = 52;
    this->rightOrientation[2].h = 35;

    this->rightOrientation[3].x = 160;
    this->rightOrientation[3].y = 105;
    this->rightOrientation[3].w = 52;
    this->rightOrientation[3].h = 35;
}
