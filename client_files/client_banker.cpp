
#include <iostream>
#include "client_banker.h"


Banker::Banker(SDL_Renderer* gRenderer) {
    this->gRenderer = gRenderer;
    if(!this->bankerTexture.loadFromFile("media/images/banker.png", gRenderer)) {
		std::cout << "Failed to load banker texture!\n" << std::endl;
	}
    this->posX = 0;
    this->posY = 0;
}


void Banker::load(int posX, int posY) {
    this->posX = posX;
    this->posY = posY;
    this->bankerClip = {0, 0, 24, 45};    
}



void Banker::render(SDL_Rect &camera) {
    this->bankerTexture.render(posX-camera.x, posY-camera.y, this->gRenderer, &this->bankerClip);
}


Banker::~Banker() {}


Banker::Banker(Banker&& other) {
    this->gRenderer = other.gRenderer;
    this->posX = std::move(other.posX);
    this->posY = std::move(other.posY);
    this->bankerClip = std::move(other.bankerClip);
    this->bankerTexture = std::move(other.bankerTexture);
}


Banker& Banker::operator=(Banker&& other) {
    this->gRenderer = other.gRenderer;
    this->posX = std::move(other.posX);
    this->posY = std::move(other.posY);
    this->bankerClip = std::move(other.bankerClip);
    this->bankerTexture = std::move(other.bankerTexture);
    return *this;
}



