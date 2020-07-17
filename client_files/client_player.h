#ifndef _CLIENT_PLAYER
#define _CLIENT_PLAYER

#include "client_texture.h"
#include "client_player_picture.h"
#include "client_drawable.h"
#include "client_shield.h"
#include "client_ghost.h"

#include "../common_files/common_protocol_message.h"
#include "../common_files/common_protocol_character.h"
#include "../common_files/common_protocol_codes.h"
#include "../common_files/common_message_to_server.h"

#include <vector>
#include <stdint.h>


class Player: public Drawable {
    protected:
        int16_t bodyPosX, bodyPosY;
        int16_t headPosX, headPosY;
        int16_t otherPosX, otherPosY;
        bool alive;
        int16_t headOffsetX, headOffsetY;
        uint8_t helmetId, armorId, shieldId, weaponId, itemId;
        std::vector<Clothes*> clothes;
        std::vector<Helmet*> helmets;
        std::vector<Weapon*> weapons;
        std::vector<Shield*> shields;
        PlayerPicture* playerPicture;
        EquippedPlayer* equippedPlayer;
        Ghost* ghost;


    void getPosArgs(std::vector<int16_t> &args);
    int16_t getEventId(int &itemId, std::vector<int16_t> &args);
    void load_helmets();
    void load_weapons();
    void load_shields();
    public:
        Player(int16_t bodyPosX, int16_t bodyPosY, int16_t headPosX, int16_t headPosY, uint16_t id, SDL_Renderer* gRenderer);

		MessageToServer handleEvent( SDL_Event& e, SDL_Rect &camera );
        MessageToServer handleEquipEvent(int &itemId);

		void render(SDL_Rect &camera, int &it);

		void set_position(int16_t newBodyPosX, int16_t newBodyPosY, int orientation);
        void set_camera(SDL_Rect &camera);

        void set_weapon(int weaponId);
        void set_helmet(int helmetId);
        void set_armor(int armorId);
        void set_shield(int shieldId);
        void update_alive_status(bool alive);

        uint16_t getId() const;

};

#endif
