#ifndef _DRAWABLE
#define _DRAWABLE

#include "SDL2/SDL.h"
#include "../common_protocol_message.h"
#include "client_texture.h"
#include <mutex>

#define WALKING_FRONT_ANIMATION_FRAMES 6
#define WALKING_BACK_ANIMATION_FRAMES 6
#define WALKING_LEFT_ANIMATION_FRAMES 5
#define WALKING_RIGHT_ANIMATION_FRAMES 5

class Drawable {

    protected:
        int velX, velY;
        int frame;
        int orientation;
        int drawable_speed;

    public:
        Drawable(int drawable_speed);


};


class Player : public Drawable {
    std::mutex m;
    protected:
        int bodyPosX, bodyPosY;
        int headPosX, headPosY;
        LTexture bodyTexture;
        LTexture headTexture;
        LTexture helmetTexture;

        SDL_Rect walkingFrontPlayer[ WALKING_FRONT_ANIMATION_FRAMES ];
        SDL_Rect walkingBackPlayer[ WALKING_BACK_ANIMATION_FRAMES ];
        SDL_Rect walkingLeftPlayer[ WALKING_LEFT_ANIMATION_FRAMES ];
        SDL_Rect walkingRightPlayer[ WALKING_RIGHT_ANIMATION_FRAMES ];
        SDL_Rect headOrientations[4];
        SDL_Rect helmetOrientations[4];

        void loadHeadSprite();
		void loadHelmetSprite();

    public:
        Player(int bodyPosX, int bodyPosY, int headPosX, int headPosY);

        virtual bool load_images(SDL_Renderer* gRenderer) = 0;

		ProtocolMessage handleEvent( SDL_Event& e );

		void render(SDL_Renderer *gRenderer); 

		void update_frames();

		void set_position(int newBodyPosX, int newBodyPosY, int newHeadPosX, int newHeadPosY);

};




class TallPlayer: public Player {
    
    const int PLAYER_WIDTH = 23;
    const int PLAYER_HEIGHT = 42;

    public:
        TallPlayer();

        virtual bool load_images(SDL_Renderer* gRenderer) override;

    private:
        void loadTallWalkingFrontSprite();
		void loadTallWalkingBackSprite();
		void loadTallWalkingLeftSprite();
		void loadTallWalkingRightSprite();

};




class ShortPlayer: public Player {

    const int PLAYER_WIDTH = 21;
    const int PLAYER_HEIGHT = 31;

    public:
        ShortPlayer();

        virtual bool load_images(SDL_Renderer* gRenderer) override;

    private:
        void load_front_walking_sprite();
		void load_back_walking_sprite();
		void load_left_walking_sprite();
		void load_right_walking_sprite();

};



enum PlayerMoving {
	STANDING = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4
};



#endif
