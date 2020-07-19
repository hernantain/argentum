
#include "client_text.h"

#include <iostream>

TextLabel::TextLabel(SDL_Renderer* gRenderer, std::string label) {
    if (initMedia(gRenderer, label))
        this->gRenderer = gRenderer;

}



bool TextLabel::initMedia(SDL_Renderer* gRenderer, std::string &label) {
    bool success = true;

	gFont = TTF_OpenFont("fonts/medieval.ttf", 30);
	if( gFont == NULL ) {   
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	} else {
		SDL_Color textColor = {255, 255, 255};
		if(!textTexture.loadFromRenderedText( gRenderer, gFont, label, textColor)) {
			printf( "Failed to render text texture!\n" );
			success = false;
		}
	}
	return success;    
}

int TextLabel::getWidth() {
	return textTexture.getWidth();
}


void TextLabel::render(int x, int y) {
    // std::cout << "PASA POR ACA" << std::endl;
    this->textTexture.render(x, y, gRenderer);
}


TextLabel::~TextLabel() {
    std::cout <<"DESTROYED?" << std::endl;
    textTexture.free();
	TTF_CloseFont(gFont);
}
