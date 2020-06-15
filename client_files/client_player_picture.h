#ifndef _PLAYER_PICTURE
#define _PLAYER_PICTURE

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





class PlayerPicture {
    
    Clothes* clothes;
    LTexture headTexture;
    SDL_Rect headOrientations[4];

    void set_head_sprite();
    bool load_pictures(SDL_Renderer* gRenderer);
    public:
        PlayerPicture(SDL_Renderer* gRenderer);
        
        void set_clothes(Clothes* clothes);

        void render(
            int &bodyPosX, 
            int &bodyPosY,
            int &headPosX, 
            int &headPosY, 
            SDL_Renderer* gRenderer, 
            int &orientation, int &frame);

};


#endif
