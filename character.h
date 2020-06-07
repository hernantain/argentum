#ifndef _CHARACTER
#define _CHARACTER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

#include "texture.h"

#define WALKING_FRONT_ANIMATION_FRAMES 6
#define WALKING_BACK_ANIMATION_FRAMES 6
#define WALKING_LEFT_ANIMATION_FRAMES 5
#define WALKING_RIGHT_ANIMATION_FRAMES 5


class Character {
	LTexture gTextureCharacter;

	SDL_Rect gWalkingFrontCharacter[ WALKING_FRONT_ANIMATION_FRAMES ];
	SDL_Rect gWalkingBackCharacter[ WALKING_BACK_ANIMATION_FRAMES ];
	SDL_Rect gWalkingLeftCharacter[ WALKING_LEFT_ANIMATION_FRAMES ];
	SDL_Rect gWalkingRightCharacter[ WALKING_RIGHT_ANIMATION_FRAMES ];

	int orientation;
    
	public: 

	
		static const int CHARACTER_WIDTH = 21;
		static const int CHARACTER_HEIGHT = 31;

		//Maximum axis velocity of the dot
		static const int CHARACTER_VEL = 1;

		Character();

		bool load_images(SDL_Renderer *gRenderer);

		void handleEvent( SDL_Event& e );

		void move();

		void render(SDL_Renderer *gRenderer); 

		void update_frames();

		void get_position();


		~Character();

	private:

        int mPosX, mPosY; //The X and Y offsets of the dot


        int mVelX, mVelY; //The velocity of the dot

		int frame;

		void load_front_walking_sprite();
		void load_back_walking_sprite();
		void load_left_walking_sprite();
		void load_right_walking_sprite();
};




enum CharacterMoving {
	STANDING = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4
};



#endif

