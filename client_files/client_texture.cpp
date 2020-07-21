#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>
#include <string>

#include "client_texture.h"

LTexture::LTexture() {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture() {
	free();
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer *gRenderer) {

	free();

	SDL_Texture* newTexture = NULL; 
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
		return false;
	} 
	
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0, 0 ));

	newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
	if( newTexture == NULL ) {
		printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		return false;
	}

	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;
	
	SDL_FreeSurface( loadedSurface );

	this->mTexture = newTexture;
	return true;
}

void LTexture::free() {
	//Free texture if it exists
	if(this->mTexture != NULL) {
		SDL_DestroyTexture( mTexture );
		this->mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}


void LTexture::render( int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	if( clip != NULL ) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	
	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, 0, NULL, flip );
}

int LTexture::getWidth() {
	return mWidth;
}

int LTexture::getHeight() {
	return mHeight;
}


bool LTexture::loadFromRenderedText(SDL_Renderer *gRenderer, TTF_Font *gFont, std::string textureText, SDL_Color textColor) {

	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if(textSurface == NULL) {
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	} else {
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL ) {
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		} else {
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		SDL_FreeSurface( textSurface );
	}
	
	return mTexture != NULL;
}

LTexture::LTexture(LTexture&& other) {
	this->mTexture = other.mTexture;
	this->mWidth = std::move(other.mWidth);
	this->mHeight = std::move(other.mHeight);
	other.mTexture = NULL;
}


LTexture& LTexture::operator=(LTexture&& other) {
	this->mTexture = other.mTexture;
	this->mWidth = std::move(other.mWidth);
	this->mHeight = std::move(other.mHeight);
	other.mTexture = NULL;
	return *this;
}

