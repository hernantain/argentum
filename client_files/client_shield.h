#ifndef _CLIENT_SHIELD
#define _CLIENT_SHIELD

#include <SDL2/SDL.h>
#include "client_texture.h"
#include <vector>

class Shield {

    int offset;
    
    protected:
        int id;
        Shield(int offset);
        LTexture shieldTexture;
        std::vector<SDL_Rect> walkingFrontPlayer;
        std::vector<SDL_Rect> walkingBackPlayer;
        std::vector<SDL_Rect> walkingLeftPlayer;
        std::vector<SDL_Rect> walkingRightPlayer;

        virtual bool load_pictures(SDL_Renderer* gRenderer) = 0;

    public:
        virtual void render(int &bodyPosX, int &bodyPosY, SDL_Renderer* gRenderer, int &orientation, int &frame);

        int get_id();

        virtual ~Shield();

};


#endif
