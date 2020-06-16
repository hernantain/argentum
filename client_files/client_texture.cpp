#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

#include "client_texture.h"

LTexture::LTexture() {
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture() {
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path, SDL_Renderer *gRenderer ) {

	free(); //Get rid of preexisting texture

	SDL_Texture* newTexture = NULL; //The final texture

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() ); //Load image at specified path
	if( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
		return false;
	} 
	
	//Color key image
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0, 0 ));

	//Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
	if( newTexture == NULL ) {
		printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		return false;
	}

	//Get image dimensions
	mWidth = loadedSurface->w;
	mHeight = loadedSurface->h;
	

	//Get rid of old loaded surface
	SDL_FreeSurface( loadedSurface );

	this->mTexture = newTexture;
	return true;
}

void LTexture::free() {
	//Free texture if it exists
	if( this->mTexture != NULL ) {
		SDL_DestroyTexture( mTexture );
		this->mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

// void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue ) {
// 	//Modulate texture rgb
// 	SDL_SetTextureColorMod( mTexture, red, green, blue );
// }

// void LTexture::setBlendMode( SDL_BlendMode blending ) {
// 	//Set blending function
// 	SDL_SetTextureBlendMode( mTexture, blending );
// }
		
// void LTexture::setAlpha( Uint8 alpha ) {
// 	//Modulate texture alpha
// 	SDL_SetTextureAlphaMod( mTexture, alpha );
// }

void LTexture::render( int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, SDL_RendererFlip flip) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL ) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderSetScale(gRenderer, 2.0, 2.0);		
	
	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, 0, NULL, flip );
}

int LTexture::getWidth() {
	return mWidth;
}

int LTexture::getHeight() {
	return mHeight;
}
