#ifndef _PLAYER_PICTURE
#define _PLAYER_PICTURE

#include <vector>
#include "client_texture.h"


#define WALKING_FRONT_ANIMATION_FRAMES 6
#define WALKING_BACK_ANIMATION_FRAMES 6
#define WALKING_LEFT_ANIMATION_FRAMES 5
#define WALKING_RIGHT_ANIMATION_FRAMES 5

class Clothes {
    
    int width, height;

    void load_front_walking_sprite();
    void load_left_walking_sprite();
    void load_right_walking_sprite();
    void load_back_walking_sprite();

    void loadTallWalkingFrontSprite();
    void loadTallWalkingBackSprite();
    void loadTallWalkingLeftSprite();
    void loadTallWalkingRightSprite();

    protected:
        LTexture bodyTexture;
        SDL_Rect walkingFrontPlayer[ WALKING_FRONT_ANIMATION_FRAMES ];
        SDL_Rect walkingBackPlayer[ WALKING_BACK_ANIMATION_FRAMES ];
        SDL_Rect walkingLeftPlayer[ WALKING_LEFT_ANIMATION_FRAMES ];
        SDL_Rect walkingRightPlayer[ WALKING_RIGHT_ANIMATION_FRAMES ];

        virtual bool load_pictures(SDL_Renderer* gRenderer) = 0;
        void set_tall_sprites();
        void set_short_sprites();

        Clothes(int width, int height);
    public:
        virtual void render(int &bodyPosX, int &bodyPosY, SDL_Renderer* gRenderer, int &orientation, int &frame);
};


class CommonTallClothes: public Clothes {

    public:
        CommonTallClothes(SDL_Renderer* gRenderer, int width, int height);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;
};


class PlateTallArmor: public Clothes {

    public:
        PlateTallArmor(SDL_Renderer* gRenderer, int width, int height);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;
};



class LeatherTallArmor: public Clothes {

    public:
        LeatherTallArmor(SDL_Renderer* gRenderer, int width, int height);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;
};


class CommonShortClothes: public Clothes {

    public:
        CommonShortClothes(SDL_Renderer* gRenderer, int width, int height);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;
};


class PlateShortArmor: public Clothes {

    public:
        PlateShortArmor(SDL_Renderer* gRenderer, int width, int height);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;
};



class LeatherShortArmor: public Clothes {

    public:
        LeatherShortArmor(SDL_Renderer* gRenderer, int width, int height);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;
};


class Picture {

    protected:
        virtual void render(
            int &bodyPosX, 
            int &bodyPosY,
            int &headPosX, 
            int &headPosY, 
            SDL_Renderer* gRenderer, 
            int &orientation, 
            int &frame) = 0;

};



class PlayerPicture: public Picture {
    
    Clothes* clothes;
    LTexture headTexture;
    SDL_Rect headOrientations[4];

    void set_head_sprite();
    bool load_pictures(SDL_Renderer* gRenderer, const char* head_path);
    public:
        PlayerPicture(SDL_Renderer* gRenderer, const char* head_path);
        
        void set_clothes(Clothes* clothes);

        virtual void render(
            int &bodyPosX, 
            int &bodyPosY,
            int &headPosX, 
            int &headPosY, 
            SDL_Renderer* gRenderer, 
            int &orientation, 
            int &frame) override;
};










class Helmet {

    int offset;
    void load_front_walking_sprite();
    void load_left_walking_sprite();
    void load_right_walking_sprite();
    void load_back_walking_sprite();

    protected:
        Helmet(int offset);
        LTexture helmetTexture;
        SDL_Rect helmetOrientation[ 4 ];
        virtual bool load_pictures(SDL_Renderer* gRenderer) = 0;

    public:
        virtual void render(int &headPosX, int &headPosY, SDL_Renderer* gRenderer, int &orientation, int &frame);

};


class Hood: public Helmet {

    void set_sprites();
    public:
        Hood(SDL_Renderer* gRenderer);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

};


class IronHelmet: public Helmet {

    void set_sprites();
    public:
        IronHelmet(SDL_Renderer* gRenderer);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

};


class MagicHat: public Helmet {

    void set_sprites();
    public:
        MagicHat(SDL_Renderer* gRenderer);

        virtual bool load_pictures(SDL_Renderer* gRenderer) override;

};



class HelmetPicture: public Picture {

    Helmet* activeHat;

};


class Equipment: public Picture {

    PlayerPicture* player;
    Helmet* helmet;
    public: 
        Equipment(PlayerPicture* player);

        void setHelmet(Helmet* helmet);

        virtual void render(
            int &bodyPosX, 
            int &bodyPosY,
            int &headPosX, 
            int &headPosY, 
            SDL_Renderer* gRenderer, 
            int &orientation, 
            int &frame) override;
};


#endif
