#ifndef _CLIENT_PRIEST
#define _CLIENT_PRIEST

#include <SDL2/SDL.h>
#include "client_texture.h"

class Priest {
    SDL_Renderer* gRenderer;
    int posX, posY;
    LTexture priestTexture;
    SDL_Rect priestClip;
    public:
        Priest(SDL_Renderer* gRenderer);

        void load(int posX, int posY);

        void render(SDL_Rect &camera);

        Priest(Priest&& other);
        Priest& operator=(Priest&& other);

        Priest(const Priest&) = delete;
        Priest& operator=(const Priest&) = delete;

        ~Priest();
};



#endif


