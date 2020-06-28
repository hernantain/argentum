#ifndef _CLIENT_PLAYER
#define _CLIENT_PLAYER

#include "client_texture.h"
#include "client_player_picture.h"
#include "client_drawable.h"

#include "../common_protocol_message.h"
#include "../common_protocol_character.h"

#include <vector>
#include <mutex>


class Player : public Drawable {
    std::mutex m;
    protected:
        int bodyPosX, bodyPosY;
        int headPosX, headPosY;
        int helmetId, armorId, shieldId, weaponId;
        std::vector<Clothes*> clothes;
        std::vector<Helmet*> helmets;
        PlayerPicture* playerPicture;
        EquippedPlayer* equippedPlayer;

    void load_helmets(SDL_Renderer* gRenderer);
    public:
        Player(int bodyPosX, int bodyPosY, int headPosX, int headPosY);

		ProtocolMessage handleEvent( SDL_Event& e );

		void render(SDL_Renderer *gRenderer, int camPosX, int camPosY); 

		void update_frames();

		void set_position(int newBodyPosX, int newBodyPosY, int newHeadPosX, int newHeadPosY);
        void set_camera(SDL_Rect &camera);

        void set_helmet(int helmetId);
        void set_armor(int armorId);

        int getPosX() const;
        int getPosY() const;

};


enum PlayerMoving {
	STANDING = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4
};

#endif
