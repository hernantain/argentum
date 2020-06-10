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
	mPosX(0), 
	mPosY(0), 
	mVelX(0), 
	mVelY(0), 
	frame(0), 
	notified(true) {
		orientation = STANDING;
	}


bool Character::load_images(SDL_Renderer *gRenderer) {

	//Load sprite sheet texture
	if( !this->gTextureCharacter.loadFromFile( "images/character.png", gRenderer ) ) {
		printf( "Failed to load walking animation texture!\n" );
		return false;
	}
	
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
				mVelY -= CHARACTER_VEL; 
				orientation = UP;
				break;

            case SDLK_DOWN: 
				mVelY += CHARACTER_VEL;
				orientation = DOWN;
				break;

            case SDLK_LEFT: 
				mVelX -= CHARACTER_VEL;
				orientation = LEFT; 
				break;
            case SDLK_RIGHT: 
				mVelX += CHARACTER_VEL; 
				orientation = RIGHT;
				break;

        }

	} else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
		switch( e.key.keysym.sym ) { 						//Adjust velocity
			case SDLK_UP: 
				mVelY += CHARACTER_VEL; 
				orientation = STANDING;
				break;

            case SDLK_DOWN: 
				mVelY -= CHARACTER_VEL; 
				orientation = STANDING;
				break;

            case SDLK_LEFT: 
				mVelX += CHARACTER_VEL; 
				orientation = STANDING;
				break;

            case SDLK_RIGHT: 
				mVelX -= CHARACTER_VEL; 
				orientation = STANDING;
				break;

        }

	} else if ( e.type == SDL_MOUSEBUTTONDOWN) {
		
		// CODIGO PARA CUANDO QUERRAMOS MANEJAR EL CLICK DEL PERSONAJE
		// int x, y; 
		// SDL_GetMouseState( &x, &y ); 
		// Event * ev = new MouseClickEvent(x,y);
		// this->pq.push(ev);
	}

	ProtocolMessage msg((uint16_t) 1, (uint16_t) this->mPosX, (uint16_t) this->mPosY, (int16_t) this->mVelX, (int16_t) this->mVelY);
	return std::move(msg);
}


void Character::set_position(int newPosX, int newPosY) {
	std::unique_lock<std::mutex> lock(this->m);
	this->mPosX = newPosX;
	this->mPosY = newPosY;
}



void Character::render(SDL_Renderer* gRenderer) {
	
	
	std::unique_lock<std::mutex> lock(this->m);
	//Show Character
	if (orientation == RIGHT) {
		SDL_Rect *currentClip = &this->gWalkingRightCharacter[ this->frame / 5 ];
		this->gTextureCharacter.render(mPosX,
										mPosY,
										gRenderer,
										currentClip);
	} else if(orientation == LEFT)  {
		SDL_Rect *currentClip = &this->gWalkingLeftCharacter[ this->frame / 5 ];
		this->gTextureCharacter.render(mPosX,
										mPosY,
										gRenderer,
										currentClip);
	} else if(orientation == UP)  {
		SDL_Rect *currentClip = &this->gWalkingBackCharacter[ this->frame / 6 ];
		this->gTextureCharacter.render(mPosX,
										mPosY,
										gRenderer,
										currentClip);
	} else if(orientation == DOWN)  {
		SDL_Rect *currentClip = &this->gWalkingFrontCharacter[ this->frame / 6 ];
		this->gTextureCharacter.render(mPosX,
										mPosY,
										gRenderer,
										currentClip);
	} else {
		SDL_Rect* currentClip = &this->gWalkingFrontCharacter[0];
		this->gTextureCharacter.render( mPosX, mPosY, gRenderer, currentClip);
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


void Character::get_position() {
	std::cout << "X: " << this->mPosX << " // Y: " << this->mPosY << std::endl;
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
	this->gWalkingFrontCharacter[0].x = 2;
	this->gWalkingFrontCharacter[0].y = 13;
	this->gWalkingFrontCharacter[0].w = 21;
	this->gWalkingFrontCharacter[0].h = 31;

	this->gWalkingFrontCharacter[1].x = 27;
	this->gWalkingFrontCharacter[1].y = 13;
	this->gWalkingFrontCharacter[1].w = 21;
	this->gWalkingFrontCharacter[1].h = 31;

	this->gWalkingFrontCharacter[2].x = 52;
	this->gWalkingFrontCharacter[2].y = 13;
	this->gWalkingFrontCharacter[2].w = 21;
	this->gWalkingFrontCharacter[2].h = 31;

	this->gWalkingFrontCharacter[3].x = 77;
	this->gWalkingFrontCharacter[3].y = 13;
	this->gWalkingFrontCharacter[3].w = 21;
	this->gWalkingFrontCharacter[3].h = 31;

	this->gWalkingFrontCharacter[4].x = 102;
	this->gWalkingFrontCharacter[4].y = 13;
	this->gWalkingFrontCharacter[4].w = 21;
	this->gWalkingFrontCharacter[4].h = 31;

	this->gWalkingFrontCharacter[5].x = 127;
	this->gWalkingFrontCharacter[5].y = 13;
	this->gWalkingFrontCharacter[5].w = 21;
	this->gWalkingFrontCharacter[5].h = 31;
}


void Character::load_back_walking_sprite() {
	this->gWalkingBackCharacter[0].x = 2;
	this->gWalkingBackCharacter[0].y = 58;
	this->gWalkingBackCharacter[0].w = 21;
	this->gWalkingBackCharacter[0].h = 31;

	this->gWalkingBackCharacter[1].x = 27;
	this->gWalkingBackCharacter[1].y = 58;
	this->gWalkingBackCharacter[1].w = 21;
	this->gWalkingBackCharacter[1].h = 31;

	this->gWalkingBackCharacter[2].x = 52;
	this->gWalkingBackCharacter[2].y = 58;
	this->gWalkingBackCharacter[2].w = 21;
	this->gWalkingBackCharacter[2].h = 31;

	this->gWalkingBackCharacter[3].x = 77;
	this->gWalkingBackCharacter[3].y = 58;
	this->gWalkingBackCharacter[3].w = 21;
	this->gWalkingBackCharacter[3].h = 31;

	this->gWalkingBackCharacter[4].x = 102;
	this->gWalkingBackCharacter[4].y = 58;
	this->gWalkingBackCharacter[4].w = 21;
	this->gWalkingBackCharacter[4].h = 31;

	this->gWalkingBackCharacter[5].x = 127;
	this->gWalkingBackCharacter[5].y = 58;
	this->gWalkingBackCharacter[5].w = 21;
	this->gWalkingBackCharacter[5].h = 31;
}


void Character::load_left_walking_sprite() {
	this->gWalkingLeftCharacter[0].x = 2;
	this->gWalkingLeftCharacter[0].y = 103;
	this->gWalkingLeftCharacter[0].w = 21;
	this->gWalkingLeftCharacter[0].h = 31;

	this->gWalkingLeftCharacter[1].x = 27;
	this->gWalkingLeftCharacter[1].y = 103;
	this->gWalkingLeftCharacter[1].w = 21;
	this->gWalkingLeftCharacter[1].h = 31;

	this->gWalkingLeftCharacter[2].x = 52;
	this->gWalkingLeftCharacter[2].y = 103;
	this->gWalkingLeftCharacter[2].w = 21;
	this->gWalkingLeftCharacter[2].h = 31;

	this->gWalkingLeftCharacter[3].x = 77;
	this->gWalkingLeftCharacter[3].y = 103;
	this->gWalkingLeftCharacter[3].w = 21;
	this->gWalkingLeftCharacter[3].h = 31;

	this->gWalkingLeftCharacter[4].x = 102;
	this->gWalkingLeftCharacter[4].y = 103;
	this->gWalkingLeftCharacter[4].w = 21;
	this->gWalkingLeftCharacter[4].h = 31;
}


void Character::load_right_walking_sprite() {
	this->gWalkingRightCharacter[0].x = 2;
	this->gWalkingRightCharacter[0].y = 148;
	this->gWalkingRightCharacter[0].w = 21;
	this->gWalkingRightCharacter[0].h = 31;

	this->gWalkingRightCharacter[1].x = 27;
	this->gWalkingRightCharacter[1].y = 148;
	this->gWalkingRightCharacter[1].w = 21;
	this->gWalkingRightCharacter[1].h = 31;

	this->gWalkingRightCharacter[2].x = 52;
	this->gWalkingRightCharacter[2].y = 148;
	this->gWalkingRightCharacter[2].w = 21;
	this->gWalkingRightCharacter[2].h = 31;

	this->gWalkingRightCharacter[3].x = 77;
	this->gWalkingRightCharacter[3].y = 148;
	this->gWalkingRightCharacter[3].w = 21;
	this->gWalkingRightCharacter[3].h = 31;

	this->gWalkingRightCharacter[4].x = 102;
	this->gWalkingRightCharacter[4].y = 148;
	this->gWalkingRightCharacter[4].w = 21;
	this->gWalkingRightCharacter[4].h = 31;
}

