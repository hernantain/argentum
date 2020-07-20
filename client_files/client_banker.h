#ifndef _CLIENT_BANKER
#define _CLIENT_BANKER

#include <SDL2/SDL.h>
#include "client_texture.h"

class Banker {

    SDL_Renderer* gRenderer;
    int posX, posY;
    LTexture bankerTexture;
    SDL_Rect bankerClip;
    public:
        Banker(SDL_Renderer* gRenderer);

        void load(int posX, int posY);

        void render(SDL_Rect &camera);

        Banker(Banker&& other);
        Banker& operator=(Banker&& other);

        Banker(const Banker&) = delete;
        Banker& operator=(const Banker&) = delete;

        ~Banker();

};


#endif
