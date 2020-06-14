#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <stdint.h>
#include <mutex>


#include "client_character.h"
#include "client_texture.h"
#include "../common_protocol_message.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


Character::Character() : 
	bodyPosX(0), 
	bodyPosY(25), 
	headPosX(4),
	headPosY(15),
	velX(0), 
	velY(0), 
	frame(0), 
	notified(true) {
		orientation = STANDING;
	}


bool Character::load_images(SDL_Renderer* gRenderer) {

	//Load sprite sheet texture
	if( !this->bodyTexture.loadFromFile( "images/armadura_placas_eg.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}

	if (!this->headTexture.loadFromFile("images/head.png", gRenderer)) {
		printf( "Failed to load head texture!\n" );
		return false;
	}

	if (!this->helmetTexture.loadFromFile("images/casco_hierro.png", gRenderer)) {
		printf( "Failed to load head texture!\n" );
		return false;
	}

	if (!this->tallTexture.loadFromFile("images/armadura_placas_he.png", gRenderer)) {
		printf( "Failed to load head texture!\n" );
		return false;
	}
	
	this->loadTallWalkingFrontSprite();
	this->loadTallWalkingBackSprite();
	this->loadTallWalkingLeftSprite();
	this->loadTallWalkingRightSprite();
	this->loadHelmetSprite();
	this->loadHeadSprite();
	this->load_front_walking_sprite();
	this->load_back_walking_sprite();
	this->load_left_walking_sprite();
	this->load_right_walking_sprite();

	return true;
}


ProtocolMessage Character::handleEvent( SDL_Event& e ) {
	//If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ) {
		switch( e.key.keysym.sym ) { 						//Adjust velocity
            
            case SDLK_UP: 
				velY -= CHARACTER_VEL; 
				orientation = UP;
				break;

            case SDLK_DOWN: 
				velY += CHARACTER_VEL;
				orientation = DOWN;
				break;

            case SDLK_LEFT: 
				velX -= CHARACTER_VEL;
				orientation = LEFT; 
				break;

            case SDLK_RIGHT: 
				velX += CHARACTER_VEL; 
				orientation = RIGHT;
				break;

        }

	} else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
		switch( e.key.keysym.sym ) { 						//Adjust velocity
			case SDLK_UP: 
				velY += CHARACTER_VEL; 
				break;

            case SDLK_DOWN: 
				velY -= CHARACTER_VEL; 
				break;

            case SDLK_LEFT: 
				velX += CHARACTER_VEL; 
				break;

            case SDLK_RIGHT: 
				velX -= CHARACTER_VEL; 
				break;

        }
		orientation = STANDING;

	} else if ( e.type == SDL_MOUSEBUTTONDOWN) {
		
		// CODIGO PARA CUANDO QUERRAMOS MANEJAR EL CLICK DEL PERSONAJE
		// int x, y; 
		// SDL_GetMouseState( &x, &y ); 
		// std::cout << "CLICK EN: " << x << " Y EN: " << y << std::endl; 
	}

	ProtocolMessage msg(
		(int16_t) 1, 
		(int16_t) this->bodyPosX, 
		(int16_t) this->bodyPosY,
		(int16_t) this->headPosX, 
		(int16_t) this->headPosY, 
		(int16_t) this->velX, 
		(int16_t) this->velY);
	return std::move(msg);
}


void Character::set_position(int newBodyPosX, int newBodyPosY, int newHeadPosX, int newHeadPosY) {
	std::unique_lock<std::mutex> lock(this->m);
	this->bodyPosX = newBodyPosX;
	this->bodyPosY = newBodyPosY;
	this->headPosX = newHeadPosX;
	this->headPosY = newHeadPosY;
}



void Character::render(SDL_Renderer* gRenderer) {
	
	
	std::unique_lock<std::mutex> lock(this->m);
	//Show Character
	if (orientation == RIGHT) {
		// SDL_Rect* currentClip = &this->walkingRightCharacter[ this->frame / 5 ];
		SDL_Rect* tallClip = &this->tallWalkingRightCharacter[ this->frame / 5 ];
		SDL_Rect* headClip = &this->headOrientations[1];
		SDL_Rect* helmetClip = &this->helmetOrientations[1];
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);
		this->helmetTexture.render(headPosX, headPosY, gRenderer, helmetClip);
		//this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);
		this->tallTexture.render(bodyPosX, bodyPosY, gRenderer, tallClip);
	} else if(orientation == LEFT)  {
		// SDL_Rect *currentClip = &this->walkingLeftCharacter[ this->frame / 5 ];
		SDL_Rect* tallClip = &this->tallWalkingLeftCharacter[ this->frame / 5 ];
		SDL_Rect* headClip = &this->headOrientations[2];
		SDL_Rect* helmetClip = &this->helmetOrientations[2];
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);
		this->helmetTexture.render(headPosX, headPosY, gRenderer, helmetClip);
		// this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);
		this->tallTexture.render(bodyPosX, bodyPosY, gRenderer, tallClip);
	} else if(orientation == UP)  {
		// SDL_Rect *currentClip = &this->walkingBackCharacter[ this->frame / 5 ];
		SDL_Rect* tallClip = &this->tallWalkingBackCharacter[ this->frame / 5 ];
		SDL_Rect* headClip = &this->headOrientations[3];
		SDL_Rect* helmetClip = &this->helmetOrientations[3];
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);
		this->helmetTexture.render(headPosX-1, headPosY-1, gRenderer, helmetClip);
		// this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);
		this->tallTexture.render(bodyPosX, bodyPosY, gRenderer, tallClip);
	} else if(orientation == DOWN)  {
		// SDL_Rect *currentClip = &this->walkingFrontCharacter[ this->frame / 5 ];
		SDL_Rect* tallClip = &this->tallWalkingFrontCharacter[ this->frame / 5 ];
		SDL_Rect* headClip = &this->headOrientations[0];
		SDL_Rect* helmetClip = &this->helmetOrientations[0];
		this->tallTexture.render(bodyPosX, bodyPosY, gRenderer, tallClip);
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);
		this->helmetTexture.render(headPosX-1, headPosY-1, gRenderer, helmetClip);
		// this->bodyTexture.render(bodyPosX, bodyPosY, gRenderer, currentClip);

	} else {
		// SDL_Rect* currentClip = &this->walkingFrontCharacter[0];
		SDL_Rect* tallClip = &this->tallWalkingFrontCharacter[0];
		SDL_Rect* headClip = &this->headOrientations[0];
		SDL_Rect* helmetClip = &this->helmetOrientations[0];
		this->tallTexture.render(bodyPosX, bodyPosY, gRenderer, tallClip);
		this->headTexture.render(headPosX, headPosY, gRenderer, headClip);
		this->helmetTexture.render(headPosX-1, headPosY-1, gRenderer, helmetClip);
		// this->bodyTexture.render( bodyPosX, bodyPosY, gRenderer, currentClip);
	}
	this->frame++;
}

Character::~Character() {
	// this->gTextureStanding.free();
}



void Character::update_frames() {
	if (this->frame / 5 >= 5)
		this->frame = 0;
}


/**
 * 
 * SPRITE LOADING
 * 
 * Esto NO queda asi. Hay que generalizarlo para 
 * cada sprite una vez que sepamos que sprites vamos a usar
 * 
 * Por ahora queda hardcodeado para el sprite de testing que estoy usando.
 * 
 */

void Character::load_front_walking_sprite() {
	this->walkingFrontCharacter[0].x = 2;
	this->walkingFrontCharacter[0].y = 13;
	this->walkingFrontCharacter[0].w = 21;
	this->walkingFrontCharacter[0].h = 31;

	this->walkingFrontCharacter[1].x = 27;
	this->walkingFrontCharacter[1].y = 13;
	this->walkingFrontCharacter[1].w = 21;
	this->walkingFrontCharacter[1].h = 31;

	this->walkingFrontCharacter[2].x = 52;
	this->walkingFrontCharacter[2].y = 13;
	this->walkingFrontCharacter[2].w = 21;
	this->walkingFrontCharacter[2].h = 31;

	this->walkingFrontCharacter[3].x = 77;
	this->walkingFrontCharacter[3].y = 13;
	this->walkingFrontCharacter[3].w = 21;
	this->walkingFrontCharacter[3].h = 31;

	this->walkingFrontCharacter[4].x = 102;
	this->walkingFrontCharacter[4].y = 13;
	this->walkingFrontCharacter[4].w = 21;
	this->walkingFrontCharacter[4].h = 31;

	this->walkingFrontCharacter[5].x = 127;
	this->walkingFrontCharacter[5].y = 13;
	this->walkingFrontCharacter[5].w = 21;
	this->walkingFrontCharacter[5].h = 31;
}


void Character::load_back_walking_sprite() {
	this->walkingBackCharacter[0].x = 2;
	this->walkingBackCharacter[0].y = 58;
	this->walkingBackCharacter[0].w = 21;
	this->walkingBackCharacter[0].h = 31;

	this->walkingBackCharacter[1].x = 27;
	this->walkingBackCharacter[1].y = 58;
	this->walkingBackCharacter[1].w = 21;
	this->walkingBackCharacter[1].h = 31;

	this->walkingBackCharacter[2].x = 52;
	this->walkingBackCharacter[2].y = 58;
	this->walkingBackCharacter[2].w = 21;
	this->walkingBackCharacter[2].h = 31;

	this->walkingBackCharacter[3].x = 77;
	this->walkingBackCharacter[3].y = 58;
	this->walkingBackCharacter[3].w = 21;
	this->walkingBackCharacter[3].h = 31;

	this->walkingBackCharacter[4].x = 102;
	this->walkingBackCharacter[4].y = 58;
	this->walkingBackCharacter[4].w = 21;
	this->walkingBackCharacter[4].h = 31;

	this->walkingBackCharacter[5].x = 127;
	this->walkingBackCharacter[5].y = 58;
	this->walkingBackCharacter[5].w = 21;
	this->walkingBackCharacter[5].h = 31;
}


void Character::load_left_walking_sprite() {
	this->walkingLeftCharacter[0].x = 2;
	this->walkingLeftCharacter[0].y = 103;
	this->walkingLeftCharacter[0].w = 21;
	this->walkingLeftCharacter[0].h = 31;

	this->walkingLeftCharacter[1].x = 27;
	this->walkingLeftCharacter[1].y = 103;
	this->walkingLeftCharacter[1].w = 21;
	this->walkingLeftCharacter[1].h = 31;

	this->walkingLeftCharacter[2].x = 52;
	this->walkingLeftCharacter[2].y = 103;
	this->walkingLeftCharacter[2].w = 21;
	this->walkingLeftCharacter[2].h = 31;

	this->walkingLeftCharacter[3].x = 77;
	this->walkingLeftCharacter[3].y = 103;
	this->walkingLeftCharacter[3].w = 21;
	this->walkingLeftCharacter[3].h = 31;

	this->walkingLeftCharacter[4].x = 102;
	this->walkingLeftCharacter[4].y = 103;
	this->walkingLeftCharacter[4].w = 21;
	this->walkingLeftCharacter[4].h = 31;
}


void Character::load_right_walking_sprite() {
	this->walkingRightCharacter[0].x = 2;
	this->walkingRightCharacter[0].y = 148;
	this->walkingRightCharacter[0].w = 21;
	this->walkingRightCharacter[0].h = 31;

	this->walkingRightCharacter[1].x = 27;
	this->walkingRightCharacter[1].y = 148;
	this->walkingRightCharacter[1].w = 21;
	this->walkingRightCharacter[1].h = 31;

	this->walkingRightCharacter[2].x = 52;
	this->walkingRightCharacter[2].y = 148;
	this->walkingRightCharacter[2].w = 21;
	this->walkingRightCharacter[2].h = 31;

	this->walkingRightCharacter[3].x = 77;
	this->walkingRightCharacter[3].y = 148;
	this->walkingRightCharacter[3].w = 21;
	this->walkingRightCharacter[3].h = 31;

	this->walkingRightCharacter[4].x = 102;
	this->walkingRightCharacter[4].y = 148;
	this->walkingRightCharacter[4].w = 21;
	this->walkingRightCharacter[4].h = 31;
}



void Character::loadHeadSprite() {
	this->headOrientations[0].x = 1;
	this->headOrientations[0].y = 0;
	this->headOrientations[0].w = 15;
	this->headOrientations[0].h = 17;

	this->headOrientations[1].x = 18;
	this->headOrientations[1].y = 0;
	this->headOrientations[1].w = 15;
	this->headOrientations[1].h = 17;

	this->headOrientations[2].x = 36;
	this->headOrientations[2].y = 0;
	this->headOrientations[2].w = 15;
	this->headOrientations[2].h = 17;

	this->headOrientations[3].x = 52;
	this->headOrientations[3].y = 0;
	this->headOrientations[3].w = 15;
	this->headOrientations[3].h = 17;
}

void Character::loadHelmetSprite() {
	this->helmetOrientations[0].x = 0;
	this->helmetOrientations[0].y = 0;
	this->helmetOrientations[0].w = 17;
	this->helmetOrientations[0].h = 17;

	this->helmetOrientations[1].x = 17;
	this->helmetOrientations[1].y = 0;
	this->helmetOrientations[1].w = 17;
	this->helmetOrientations[1].h = 17;

	this->helmetOrientations[2].x = 34;
	this->helmetOrientations[2].y = 0;
	this->helmetOrientations[2].w = 17;
	this->helmetOrientations[2].h = 17;

	this->helmetOrientations[3].x = 51;
	this->helmetOrientations[3].y = 0;
	this->helmetOrientations[3].w = 17;
	this->helmetOrientations[3].h = 17;
}


void Character::loadTallWalkingFrontSprite() {
	this->tallWalkingFrontCharacter[0].x = 1;
	this->tallWalkingFrontCharacter[0].y = 2;
	this->tallWalkingFrontCharacter[0].w = 23;
	this->tallWalkingFrontCharacter[0].h = 42;

	this->tallWalkingFrontCharacter[1].x = 26;
	this->tallWalkingFrontCharacter[1].y = 2;
	this->tallWalkingFrontCharacter[1].w = 23;
	this->tallWalkingFrontCharacter[1].h = 42;

	this->tallWalkingFrontCharacter[2].x = 51;
	this->tallWalkingFrontCharacter[2].y = 2;
	this->tallWalkingFrontCharacter[2].w = 23;
	this->tallWalkingFrontCharacter[2].h = 42;

	this->tallWalkingFrontCharacter[3].x = 76;
	this->tallWalkingFrontCharacter[3].y = 2;
	this->tallWalkingFrontCharacter[3].w = 23;
	this->tallWalkingFrontCharacter[3].h = 42;

	this->tallWalkingFrontCharacter[4].x = 101;
	this->tallWalkingFrontCharacter[4].y = 2;
	this->tallWalkingFrontCharacter[4].w = 23;
	this->tallWalkingFrontCharacter[4].h = 42;

	this->tallWalkingFrontCharacter[5].x = 126;
	this->tallWalkingFrontCharacter[5].y = 2;
	this->tallWalkingFrontCharacter[5].w = 23;
	this->tallWalkingFrontCharacter[5].h = 42;
}



void Character::loadTallWalkingBackSprite() {
	this->tallWalkingBackCharacter[0].x = 1;
	this->tallWalkingBackCharacter[0].y = 48;
	this->tallWalkingBackCharacter[0].w = 23;
	this->tallWalkingBackCharacter[0].h = 42;

	this->tallWalkingBackCharacter[1].x = 26;
	this->tallWalkingBackCharacter[1].y = 48;
	this->tallWalkingBackCharacter[1].w = 23;
	this->tallWalkingBackCharacter[1].h = 42;

	this->tallWalkingBackCharacter[2].x = 51;
	this->tallWalkingBackCharacter[2].y = 48;
	this->tallWalkingBackCharacter[2].w = 23;
	this->tallWalkingBackCharacter[2].h = 42;

	this->tallWalkingBackCharacter[3].x = 76;
	this->tallWalkingBackCharacter[3].y = 48;
	this->tallWalkingBackCharacter[3].w = 23;
	this->tallWalkingBackCharacter[3].h = 42;

	this->tallWalkingBackCharacter[4].x = 101;
	this->tallWalkingBackCharacter[4].y = 48;
	this->tallWalkingBackCharacter[4].w = 23;
	this->tallWalkingBackCharacter[4].h = 42;

	this->tallWalkingBackCharacter[5].x = 126;
	this->tallWalkingBackCharacter[5].y = 48;
	this->tallWalkingBackCharacter[5].w = 23;
	this->tallWalkingBackCharacter[5].h = 42;
}


void Character::loadTallWalkingLeftSprite() {
	this->tallWalkingLeftCharacter[0].x = 1;
	this->tallWalkingLeftCharacter[0].y = 93;
	this->tallWalkingLeftCharacter[0].w = 23;
	this->tallWalkingLeftCharacter[0].h = 42;

	this->tallWalkingLeftCharacter[1].x = 23;
	this->tallWalkingLeftCharacter[1].y = 93;
	this->tallWalkingLeftCharacter[1].w = 23;
	this->tallWalkingLeftCharacter[1].h = 42;

	this->tallWalkingLeftCharacter[2].x = 49;
	this->tallWalkingLeftCharacter[2].y = 93;
	this->tallWalkingLeftCharacter[2].w = 23;
	this->tallWalkingLeftCharacter[2].h = 42;

	this->tallWalkingLeftCharacter[3].x = 74;
	this->tallWalkingLeftCharacter[3].y = 93;
	this->tallWalkingLeftCharacter[3].w = 23;
	this->tallWalkingLeftCharacter[3].h = 42;

	this->tallWalkingLeftCharacter[4].x = 99;
	this->tallWalkingLeftCharacter[4].y = 93;
	this->tallWalkingLeftCharacter[4].w = 23;
	this->tallWalkingLeftCharacter[4].h = 42;
}


void Character::loadTallWalkingRightSprite() {
	this->tallWalkingRightCharacter[0].x = 1;
	this->tallWalkingRightCharacter[0].y = 138;
	this->tallWalkingRightCharacter[0].w = 23;
	this->tallWalkingRightCharacter[0].h = 42;

	this->tallWalkingRightCharacter[1].x = 29;
	this->tallWalkingRightCharacter[1].y = 138;
	this->tallWalkingRightCharacter[1].w = 23;
	this->tallWalkingRightCharacter[1].h = 42;

	this->tallWalkingRightCharacter[2].x = 54;
	this->tallWalkingRightCharacter[2].y = 138;
	this->tallWalkingRightCharacter[2].w = 23;
	this->tallWalkingRightCharacter[2].h = 42;

	this->tallWalkingRightCharacter[3].x = 78;
	this->tallWalkingRightCharacter[3].y = 138;
	this->tallWalkingRightCharacter[3].w = 23;
	this->tallWalkingRightCharacter[3].h = 42;

	this->tallWalkingRightCharacter[4].x = 103;
	this->tallWalkingRightCharacter[4].y = 138;
	this->tallWalkingRightCharacter[4].w = 23;
	this->tallWalkingRightCharacter[4].h = 42;
}
