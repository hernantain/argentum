
#include "client_player.h"
#include "client_drawable.h"


Drawable::Drawable(
    uint16_t id, 
    SDL_Renderer* gRenderer) : id(id),
                                orientation(STANDING){
    this->gRenderer = gRenderer;
}

