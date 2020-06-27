#ifndef _CHARACTER
#define _CHARACTER

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <mutex>
#include <atomic>
#include <condition_variable>

#include "../common_protocol_message.h"
#include "../common_protocol_character.h"
#include "client_texture.h"

#define WALKING_FRONT_ANIMATION_FRAMES 6
#define WALKING_BACK_ANIMATION_FRAMES 6
#define WALKING_LEFT_ANIMATION_FRAMES 5
#define WALKING_RIGHT_ANIMATION_FRAMES 5


class Character {

	int bodyPosX, bodyPosY; //The X and Y offsets of the character
	int headPosX, headPosY;
	int velX, velY; //The velocity of the character
	int frame;
	std::atomic<bool>notified;
	std::condition_variable cond_var;
	std::mutex m;
	int orientation;
	
	LTexture bodyTexture;
	LTexture headTexture;

	SDL_Rect walkingFrontCharacter[ WALKING_FRONT_ANIMATION_FRAMES ];
	SDL_Rect walkingBackCharacter[ WALKING_BACK_ANIMATION_FRAMES ];
	SDL_Rect walkingLeftCharacter[ WALKING_LEFT_ANIMATION_FRAMES ];
	SDL_Rect walkingRightCharacter[ WALKING_RIGHT_ANIMATION_FRAMES ];
	SDL_Rect headOrientations[4];
    
	public: 

	
		static const int CHARACTER_WIDTH = 21;
		static const int CHARACTER_HEIGHT = 31;

		static const int CHARACTER_VEL = 3; //Maximum axis velocity of the dot

		Character();

		bool load_images(SDL_Renderer *gRenderer);

		ProtocolMessage handleEvent( SDL_Event& e );

		void move();

		void render(SDL_Renderer *gRenderer); 

		void update_frames();

		void get_position();

		void set_position(int newBodyPosX, int newBodyPosY, int newHeadPosX, int newHeadPosY);

		~Character();

	private:
		void load_front_walking_sprite();
		void load_back_walking_sprite();
		void load_left_walking_sprite();
		void load_right_walking_sprite();
		void loadHeadSprite();
};



enum CharacterMoving {
	STANDING = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4
};



#endif

