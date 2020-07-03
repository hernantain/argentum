#ifndef _CLIENT_TALL_PLAYER
#define _CLIENT_TALL_PLAYER

#include <SDL2/SDL.h>
#include <stdint.h>
#include "client_player.h"


class TallPlayer: public Player {
    
    const int PLAYER_WIDTH = 23;
    const int PLAYER_HEIGHT = 42;

    public:
        TallPlayer(SDL_Renderer* gRenderer, const char* head_path, int16_t id, int bodyPosX, int bodyPosY);

    private:
        void load_clothes();

};



#endif

