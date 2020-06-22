
#include "client_window.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

LWindow::LWindow() {
	//Initialize non-existant window
	mWindow = NULL;
	mFullScreen = false;
	mMinimized = false;
	mWidth = 0;
	mHeight = 0;
}

bool LWindow::init() {
	//Create window
	mWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	if( mWindow != NULL ) {
		mWidth = SCREEN_WIDTH;
		mHeight = SCREEN_HEIGHT;
	}

	return mWindow != NULL;
}


SDL_Renderer* LWindow::createRenderer() {
    this->gRenderer = SDL_CreateRenderer( mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	return this->gRenderer;
}


void LWindow::handleEvent( SDL_Event& e ) {
	//Window event occured
	if( e.type == SDL_WINDOWEVENT )
	{

		switch( e.window.event )
		{
			//Get new dimensions and repaint on window size change
			case SDL_WINDOWEVENT_SIZE_CHANGED:
                mWidth = e.window.data1;
                mHeight = e.window.data2;
                SDL_RenderPresent( gRenderer );
			    break;

			//Repaint on exposure
			case SDL_WINDOWEVENT_EXPOSED:
			    SDL_RenderPresent( gRenderer );
			    break;

			//Window minimized
			case SDL_WINDOWEVENT_MINIMIZED:
                mMinimized = true;
                break;

			//Window maxized
			case SDL_WINDOWEVENT_MAXIMIZED:
                mMinimized = false;
                break;
			
			//Window restored
			case SDL_WINDOWEVENT_RESTORED:
                mMinimized = false;
                break;
		}
	}


	else if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN ) {
		if( mFullScreen ) {
			SDL_SetWindowFullscreen( mWindow, SDL_FALSE );
			mFullScreen = false;
		} else {
			SDL_SetWindowFullscreen( mWindow, SDL_TRUE );
			mFullScreen = true;
			mMinimized = false;
		}
	}
}


void LWindow::free() {
	if( mWindow != NULL )
		SDL_DestroyWindow( mWindow );

	mWidth = 0;
	mHeight = 0;
}


int LWindow::getWidth() {
	return mWidth;
}


int LWindow::getHeight() {
	return mHeight;
}


bool LWindow::isMinimized() {
	return mMinimized;
}
