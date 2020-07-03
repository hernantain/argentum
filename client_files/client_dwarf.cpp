
#include "client_dwarf.h"

Dwarf::Dwarf(
    SDL_Renderer* gRenderer, 
    int16_t id, 
    int bodyPosX, 
    int bodyPosY) : ShortPlayer(
                        gRenderer, 
                        "images/enano.png", 
                        id,
                        bodyPosX, 
                        bodyPosY) {}
