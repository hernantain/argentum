#ifndef _PLAYER_PICTURE
#define _PLAYER_PICTURE

#include <vector>
#include "client_texture.h"
#include "client_clothes.h"
#include "client_helmet.h"
#include "client_weapon.h"


class Picture {

    protected:
        virtual void render(
            int bodyPosX, 
            int bodyPosY,
            int headPosX, 
            int headPosY, 
            SDL_Renderer* gRenderer, 
            int &orientation, 
            int &frame) = 0;

};


class PlayerPicture: public Picture {
    
    Clothes* clothes;
    LTexture headTexture;
    // SDL_Rect headOrientations[4];
    std::vector<SDL_Rect> headOrientations;

    void set_head_sprite();
    bool load_pictures(SDL_Renderer* gRenderer, const char* head_path);
    public:
        PlayerPicture(SDL_Renderer* gRenderer, const char* head_path);
        
        void set_clothes(Clothes* clothes);

        virtual void render(
            int bodyPosX, 
            int bodyPosY,
            int headPosX, 
            int headPosY, 
            SDL_Renderer* gRenderer, 
            int &orientation, 
            int &frame) override;
};


class EquippedPlayer: public Picture {

    PlayerPicture* player;
    Helmet* helmet;
    Weapon* weapon;

    public: 
        EquippedPlayer(PlayerPicture* player);

        void setHelmet(Helmet* helmet);
        void setWeapon(Weapon* weapon);
        
        virtual void render(
            int bodyPosX, 
            int bodyPosY,
            int headPosX, 
            int headPosY, 
            SDL_Renderer* gRenderer, 
            int &orientation, 
            int &frame) override;
};


#endif
