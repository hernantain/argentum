#ifndef _CLIENT_TEXT
#define _CLIENT_TEXT


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "client_texture.h"


class TextLabel {

    SDL_Renderer* gRenderer;
    LTexture textTexture;
    TTF_Font* gFont;

    bool initMedia(SDL_Renderer* gRenderer, std::string &label);
    public:
        TextLabel(SDL_Renderer* gRenderer, std::string label);

        void render(int x, int y);

        int getWidth();

        ~TextLabel();

};


#endif

