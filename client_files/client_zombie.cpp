
#include "client_zombie.h"


Zombie::Zombie(SDL_Renderer* gRenderer) : NpcPicture(gRenderer) {
    if (this->load_pictures("media/images/zombie.png"))
        this->set_sprites();
}


Zombie::~Zombie() {}


void Zombie::set_sprites() {
    this->load_front_walking_sprite();  
    this->load_back_walking_sprite();
    this->load_left_walking_sprite();
    this->load_right_walking_sprite();
}


void Zombie::render(int posX, int posY, SDL_Renderer* gRenderer, int &orientation, int &frame) {
    // Show Zombie
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




void Zombie::load_front_walking_sprite() {
    this->frontOrientation[0].x = 0;
    this->frontOrientation[0].y = 0;
    this->frontOrientation[0].w = 24;
    this->frontOrientation[0].h = 48;

    this->frontOrientation[1].x = 24;
    this->frontOrientation[1].y = 0;
    this->frontOrientation[1].w = 24;
    this->frontOrientation[1].h = 48;

    this->frontOrientation[2].x = 48;
    this->frontOrientation[2].y = 0;
    this->frontOrientation[2].w = 24;
    this->frontOrientation[2].h = 48;

    this->frontOrientation[3].x = 72;
    this->frontOrientation[3].y = 0;
    this->frontOrientation[3].w = 24;
    this->frontOrientation[3].h = 48;

    this->frontOrientation[4].x = 96;
    this->frontOrientation[4].y = 0;
    this->frontOrientation[4].w = 24;
    this->frontOrientation[4].h = 48;

    this->frontOrientation[5].x = 120;
    this->frontOrientation[5].y = 0;
    this->frontOrientation[5].w = 24;
    this->frontOrientation[5].h = 48;
}


void Zombie::load_back_walking_sprite() {
    this->backOrientation[0].x = 0;
    this->backOrientation[0].y = 50;
    this->backOrientation[0].w = 24;
    this->backOrientation[0].h = 48;

    this->backOrientation[1].x = 24;
    this->backOrientation[1].y = 50;
    this->backOrientation[1].w = 24;
    this->backOrientation[1].h = 48;

    this->backOrientation[2].x = 48;
    this->backOrientation[2].y = 50;
    this->backOrientation[2].w = 24;
    this->backOrientation[2].h = 48;

    this->backOrientation[3].x = 72;
    this->backOrientation[3].y = 50;
    this->backOrientation[3].w = 24;
    this->backOrientation[3].h = 48;

    this->backOrientation[4].x = 96;
    this->backOrientation[4].y = 50;
    this->backOrientation[4].w = 24;
    this->backOrientation[4].h = 48;

    this->backOrientation[5].x = 120;
    this->backOrientation[5].y = 50;
    this->backOrientation[5].w = 24;
    this->backOrientation[5].h = 48;
}


void Zombie::load_left_walking_sprite() {
    this->leftOrientation[0].x = 0;
    this->leftOrientation[0].y = 103;
    this->leftOrientation[0].w = 16;
    this->leftOrientation[0].h = 48;

    this->leftOrientation[1].x = 16;
    this->leftOrientation[1].y = 103;
    this->leftOrientation[1].w = 16;
    this->leftOrientation[1].h = 48;

    this->leftOrientation[2].x = 37;
    this->leftOrientation[2].y = 103;
    this->leftOrientation[2].w = 16;
    this->leftOrientation[2].h = 48;

    this->leftOrientation[3].x = 57;
    this->leftOrientation[3].y = 103;
    this->leftOrientation[3].w = 16;
    this->leftOrientation[3].h = 48;

    this->leftOrientation[4].x = 75;
    this->leftOrientation[4].y = 103;
    this->leftOrientation[4].w = 16;
    this->leftOrientation[4].h = 48;
}


void Zombie::load_right_walking_sprite() {
    this->rightOrientation[0].x = 0;
    this->rightOrientation[0].y = 153;
    this->rightOrientation[0].w = 16;
    this->rightOrientation[0].h = 48;

    this->rightOrientation[1].x = 16;
    this->rightOrientation[1].y = 153;
    this->rightOrientation[1].w = 16;
    this->rightOrientation[1].h = 48;

    this->rightOrientation[2].x = 37;
    this->rightOrientation[2].y = 153;
    this->rightOrientation[2].w = 16;
    this->rightOrientation[2].h = 48;

    this->rightOrientation[3].x = 57;
    this->rightOrientation[3].y = 153;
    this->rightOrientation[3].w = 16;
    this->rightOrientation[3].h = 48;

    this->rightOrientation[4].x = 75;
    this->rightOrientation[4].y = 153;
    this->rightOrientation[4].w = 16;
    this->rightOrientation[4].h = 48;
}

