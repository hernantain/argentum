#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "character.h"
#include "main_program.h"

#define WALKING_ANIMATION_FRAMES 6


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

MainProgram::MainProgram() : 
	gWindow(NULL), 
	gRenderer(NULL), 
	running(true) {}


void MainProgram::run() {
	if( !this->init() ) {
		printf( "Failed to initialize!\n" );
		return;
	}

	//Event handler
	SDL_Event e;

	//Current animation frame
	int frame = 0;

	Character character;
	if (!character.load_images(this->gRenderer))
		exit(1);


	this->skt.connect_to("localhost", "8080");

	while(this->running) {
		while( SDL_PollEvent( &e ) != 0 ) {
			if( e.type == SDL_QUIT ) {
				this->running = false;
			} else {
				
				character.handleEvent( e );
			}

			character.get_position(); // a borrar
			
		}

		character.move();

		//Clear screen
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		
		character.render(this->gRenderer);

		//Update screen
		SDL_RenderPresent( this->gRenderer );

		character.update_frames();

	}
}

bool MainProgram::init() {

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false;
	} 
	
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
		printf( "Warning: Linear texture filtering not enabled!" );
	} 

	this->gWindow = SDL_CreateWindow( "Argentum - Taller", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( this->gWindow == NULL ) {
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	} 
	
	//Create vsynced renderer for window
	this->gRenderer = SDL_CreateRenderer( this->gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if( this->gRenderer == NULL ) {
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	} 
	//Initialize renderer color
	SDL_SetRenderDrawColor( this->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}

	return true;
}


MainProgram::~MainProgram() {

	//Destroy window	
	SDL_DestroyRenderer( this->gRenderer );
	SDL_DestroyWindow( this->gWindow );
	this->gWindow = NULL;
	this->gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
