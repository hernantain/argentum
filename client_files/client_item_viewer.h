#ifndef _CLIENT_ITEM_VIEWER
#define _CLIENT_ITEM_VIEWER

#include <stdint.h>
#include <map>
#include <SDL2/SDL.h>

#include "client_texture.h"

//9
#define SWORD_IMAGE "images/16099.png"

class ItemViewer {

    SDL_Renderer* gRenderer;
    std::map<uint8_t, LTexture*>items;

    bool exists(uint8_t id);

    void add_item(uint8_t &id);
    public:
        LTexture* get_item_icon(uint8_t id);    

        ItemViewer(SDL_Renderer* gRenderer);


        void print_works();
};


#endif
