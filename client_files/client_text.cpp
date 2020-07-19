
#include "client_text.h"

#include <iostream>

TextLabel::TextLabel(SDL_Renderer* gRenderer, std::string label, int size) {
    if (initMedia(gRenderer, label, size))
        this->gRenderer = gRenderer;

}



bool TextLabel::initMedia(SDL_Renderer* gRenderer, std::string &label, int &size) {
    bool success = true;

	gFont = TTF_OpenFont("fonts/medieval.ttf", size);
	if( gFont == NULL ) {   
		printf("Failed to load medieval font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	} else {
		SDL_Color textColor = {255, 255, 255};
		if(!textTexture.loadFromRenderedText( gRenderer, gFont, label, textColor)) {
			printf("Failed to render text texture!\n");
			success = false;
		}
	}
	return success;    
}


void TextLabel::set_new_label(std::string newLabel) {
	SDL_Color textColor = {255, 255, 255};
	if(!textTexture.loadFromRenderedText( gRenderer, gFont, newLabel, textColor)) {
		printf("Failed to render text texture!\n");
		return;
	}
}


int TextLabel::getWidth() {
	return textTexture.getWidth();
}


void TextLabel::render(int x, int y) {
    // std::cout << "PASA POR ACA" << std::endl;
    this->textTexture.render(x, y, gRenderer);
}


TextLabel::~TextLabel() {
    std::cout <<"DESTROYED TEXT" << std::endl;
    textTexture.free();
	TTF_CloseFont(gFont);
}
