
#include "client_elf.h"


Elf::Elf(
    SDL_Renderer* gRenderer, 
    int16_t id, 
    int bodyPosX, 
    int bodyPosY) : TallPlayer(
                        gRenderer, 
                        "media/images/elfo.png", 
                        id,
                        bodyPosX, 
                        bodyPosY) {}
