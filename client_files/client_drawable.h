#ifndef _DRAWABLE
#define _DRAWABLE

#include "SDL2/SDL.h"
#include "../common_protocol_message.h"
#include "client_texture.h"
#include "client_player_picture.h"

#include <vector>
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
        std::vector<Clothes*> clothes;
        std::vector<Helmet*> helmets;
        PlayerPicture* playerPicture;
        Equipment* equipment;

    void load_helmets(SDL_Renderer* gRenderer);
    public:
        Player(int bodyPosX, int bodyPosY, int headPosX, int headPosY);

		ProtocolMessage handleEvent( SDL_Event& e );

		void render(SDL_Renderer *gRenderer); 

		void update_frames();

		void set_position(int newBodyPosX, int newBodyPosY, int newHeadPosX, int newHeadPosY);

};




class TallPlayer: public Player {
    
    const int PLAYER_WIDTH = 23;
    const int PLAYER_HEIGHT = 42;

    public:
        TallPlayer(SDL_Renderer* gRenderer, const char* head_path);

    private:
        void load_clothes(SDL_Renderer* gRenderer);

};




class ShortPlayer: public Player {

    const int PLAYER_WIDTH = 21;
    const int PLAYER_HEIGHT = 31;

    public:
        ShortPlayer(SDL_Renderer* gRenderer, const char* head_path);

    private:
        void load_clothes(SDL_Renderer* gRenderer);

};



class Human: public TallPlayer {

    public:
        Human(SDL_Renderer* gRenderer);

};


class Elf: public TallPlayer {

    public:
        Elf(SDL_Renderer* gRenderer);

};


class Dwarf: public ShortPlayer {

    public: 
        Dwarf(SDL_Renderer* gRenderer);

};



class Gnome: public ShortPlayer {

    public: 
        Gnome(SDL_Renderer* gRenderer);

};


enum PlayerMoving {
	STANDING = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4
};



#endif
