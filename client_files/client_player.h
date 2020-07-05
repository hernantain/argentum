#ifndef _CLIENT_PLAYER
#define _CLIENT_PLAYER

#include "client_texture.h"
#include "client_player_picture.h"
#include "client_drawable.h"

#include "../common_protocol_message.h"
#include "../common_protocol_character.h"

#include <vector>
#include <mutex>
#include <stdint.h>


class Player: public Drawable {
    std::mutex m;
    int headOffsetX, headOffsetY;
    protected:
        int bodyPosX, bodyPosY;
        int headPosX, headPosY;
        int16_t otherPosX, otherPosY;
        int helmetId, armorId, shieldId, weaponId;
        std::vector<Clothes*> clothes;
        std::vector<Helmet*> helmets;
        std::vector<Weapon*> weapons;
        PlayerPicture* playerPicture;
        EquippedPlayer* equippedPlayer;

    void load_helmets();
    void load_weapons();
    public:
        Player(int bodyPosX, int bodyPosY, int headPosX, int headPosY, int16_t id, SDL_Renderer* gRenderer);

		ProtocolMessage handleEvent( SDL_Event& e, SDL_Rect &camera );

		void render(SDL_Rect &camera, int &it);

		void update_frames();

		void set_position(int newBodyPosX, int newBodyPosY, int orientation);
        void set_camera(SDL_Rect &camera);

        void set_weapon(int weaponId);
        void set_helmet(int helmetId);
        void set_armor(int armorId);

        int getPosX() const;
        int getPosY() const;

        int16_t getId() const;

};


enum PlayerMoving {
	STANDING = 0,
	LEFT = 1,
	RIGHT = 2,
	UP = 3,
	DOWN = 4
};

#endif
