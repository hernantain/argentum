
#include "client_priest.h"

#include <iostream>



Priest::Priest(SDL_Renderer* gRenderer) {
    this->gRenderer = gRenderer;
    if(!this->priestTexture.loadFromFile("media/images/priest.png", gRenderer)) {
		std::cout << "Failed to load priest texture!\n" << std::endl;
	}

    this->posX = 0;
    this->posY = 0;
}


void Priest::load(int posX, int posY) {
    this->posX = posX;
    this->posY = posY;
    this->priestClip = {0, 0, 24, 45};    
}



void Priest::render(SDL_Rect &camera) {
    this->priestTexture.render(posX-camera.x, posY-camera.y, this->gRenderer, &this->priestClip);
}


Priest::~Priest() {}


Priest::Priest(Priest&& other) {
    this->gRenderer = other.gRenderer;
    this->posX = std::move(other.posX);
    this->posY = std::move(other.posY);
    this->priestClip = std::move(other.priestClip);
    this->priestTexture = std::move(other.priestTexture);
}


Priest& Priest::operator=(Priest&& other) {
    this->gRenderer = other.gRenderer;
    this->posX = std::move(other.posX);
    this->posY = std::move(other.posY);
    this->priestClip = std::move(other.priestClip);
    this->priestTexture = std::move(other.priestTexture);
    return *this;
}
