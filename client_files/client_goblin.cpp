
#include "client_goblin.h"


Goblin::Goblin(int16_t id, SDL_Renderer* gRenderer) : NPC(id, gRenderer) {
    if (this->load_pictures("images/goblin.png"))
        this->set_sprites();
}



void Goblin::set_sprites() {
    this->load_front_walking_sprite();  
    this->load_back_walking_sprite();
    this->load_left_walking_sprite();
    this->load_right_walking_sprite();
}


void Goblin::load_front_walking_sprite() {
    this->frontOrientation[0].x = 2;
    this->frontOrientation[0].y = 3;
    this->frontOrientation[0].w = 20;
    this->frontOrientation[0].h = 30;

    this->frontOrientation[1].x = 26;
    this->frontOrientation[1].y = 3;
    this->frontOrientation[1].w = 20;
    this->frontOrientation[1].h = 30;

    this->frontOrientation[2].x = 50;
    this->frontOrientation[2].y = 3;
    this->frontOrientation[2].w = 20;
    this->frontOrientation[2].h = 30;

    this->frontOrientation[3].x = 73;
    this->frontOrientation[3].y = 3;
    this->frontOrientation[3].w = 20;
    this->frontOrientation[3].h = 30;

    this->frontOrientation[4].x = 96;
    this->frontOrientation[4].y = 3;
    this->frontOrientation[4].w = 20;
    this->frontOrientation[4].h = 30;

    this->frontOrientation[5].x = 120;
    this->frontOrientation[5].y = 3;
    this->frontOrientation[5].w = 20;
    this->frontOrientation[5].h = 30;

    this->frontOrientation[6].x = 144;
    this->frontOrientation[6].y = 3;
    this->frontOrientation[6].w = 20;
    this->frontOrientation[6].h = 30;

    this->frontOrientation[7].x = 167;
    this->frontOrientation[7].y = 3;
    this->frontOrientation[7].w = 20;
    this->frontOrientation[7].h = 30;
}


void Goblin::load_back_walking_sprite() {
    this->backOrientation[0].x = 2;
    this->backOrientation[0].y = 34;
    this->backOrientation[0].w = 20;
    this->backOrientation[0].h = 30;

    this->backOrientation[1].x = 26;
    this->backOrientation[1].y = 34;
    this->backOrientation[1].w = 20;
    this->backOrientation[1].h = 30;

    this->backOrientation[2].x = 50;
    this->backOrientation[2].y = 34;
    this->backOrientation[2].w = 20;
    this->backOrientation[2].h = 30;

    this->backOrientation[3].x = 73;
    this->backOrientation[3].y = 34;
    this->backOrientation[3].w = 20;
    this->backOrientation[3].h = 30;

    this->backOrientation[4].x = 96;
    this->backOrientation[4].y = 34;
    this->backOrientation[4].w = 20;
    this->backOrientation[4].h = 30;

    this->backOrientation[5].x = 120;
    this->backOrientation[5].y = 34;
    this->backOrientation[5].w = 20;
    this->backOrientation[5].h = 30;

    this->backOrientation[6].x = 144;
    this->backOrientation[6].y = 34;
    this->backOrientation[6].w = 20;
    this->backOrientation[6].h = 30;

    this->backOrientation[7].x = 167;
    this->backOrientation[7].y = 34;
    this->backOrientation[7].w = 20;
    this->backOrientation[7].h = 30;
}


void Goblin::load_left_walking_sprite() {
    this->leftOrientation[0].x = 2;
    this->leftOrientation[0].y = 64;
    this->leftOrientation[0].w = 20;
    this->leftOrientation[0].h = 30;

    this->leftOrientation[1].x = 26;
    this->leftOrientation[1].y = 64;
    this->leftOrientation[1].w = 20;
    this->leftOrientation[1].h = 30;

    this->leftOrientation[2].x = 50;
    this->leftOrientation[2].y = 64;
    this->leftOrientation[2].w = 20;
    this->leftOrientation[2].h = 30;

    this->leftOrientation[3].x = 73;
    this->leftOrientation[3].y = 64;
    this->leftOrientation[3].w = 20;
    this->leftOrientation[3].h = 30;

    this->leftOrientation[4].x = 96;
    this->leftOrientation[4].y = 64;
    this->leftOrientation[4].w = 20;
    this->leftOrientation[4].h = 30;

    this->leftOrientation[5].x = 120;
    this->leftOrientation[5].y = 64;
    this->leftOrientation[5].w = 20;
    this->leftOrientation[5].h = 30;

    this->leftOrientation[6].x = 144;
    this->leftOrientation[6].y = 64;
    this->leftOrientation[6].w = 20;
    this->leftOrientation[6].h = 30;

    this->leftOrientation[7].x = 167;
    this->leftOrientation[7].y = 64;
    this->leftOrientation[7].w = 20;
    this->leftOrientation[7].h = 30;
}


void Goblin::load_right_walking_sprite() {
    this->rightOrientation[0].x = 2;
    this->rightOrientation[0].y = 64;
    this->rightOrientation[0].w = 20;
    this->rightOrientation[0].h = 30;

    this->rightOrientation[1].x = 26;
    this->rightOrientation[1].y = 64;
    this->rightOrientation[1].w = 20;
    this->rightOrientation[1].h = 30;

    this->rightOrientation[2].x = 50;
    this->rightOrientation[2].y = 64;
    this->rightOrientation[2].w = 20;
    this->rightOrientation[2].h = 30;

    this->rightOrientation[3].x = 73;
    this->rightOrientation[3].y = 64;
    this->rightOrientation[3].w = 20;
    this->rightOrientation[3].h = 30;

    this->rightOrientation[4].x = 96;
    this->rightOrientation[4].y = 64;
    this->rightOrientation[4].w = 20;
    this->rightOrientation[4].h = 30;

    this->rightOrientation[5].x = 120;
    this->rightOrientation[5].y = 64;
    this->rightOrientation[5].w = 20;
    this->rightOrientation[5].h = 30;

    this->rightOrientation[6].x = 144;
    this->rightOrientation[6].y = 64;
    this->rightOrientation[6].w = 20;
    this->rightOrientation[6].h = 30;

    this->rightOrientation[7].x = 167;
    this->rightOrientation[7].y = 64;
    this->rightOrientation[7].w = 20;
    this->rightOrientation[7].h = 30;
}
