#ifndef _CLIENT_HELMET
#define _CLIENT_HELMET

#include <SDL2/SDL.h>
#include "client_texture.h"


class Helmet {

    int offset;
    void load_front_walking_sprite();
    void load_left_walking_sprite();
    void load_right_walking_sprite();
    void load_back_walking_sprite();

    protected:
        int id;
        Helmet(int offset);
        LTexture helmetTexture;
        SDL_Rect helmetOrientation[4];
        virtual bool load_pictures(SDL_Renderer* gRenderer) = 0;

    public:
        virtual void render(int &headPosX, int &headPosY, SDL_Renderer* gRenderer, int &orientation, int &frame);

        int get_id();

};


#endif
