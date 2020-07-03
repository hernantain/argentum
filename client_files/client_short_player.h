#ifndef _CLIENT_SHORT_PLAYER
#define _CLIENT_SHORT_PLAYER

#include "client_player.h"
#include <SDL2/SDL.h>
#include <stdint.h>


class ShortPlayer: public Player {

    const int PLAYER_WIDTH = 21;
    const int PLAYER_HEIGHT = 31;

    public:
        ShortPlayer(SDL_Renderer* gRenderer, const char* head_path, int16_t id, int bodyPosX, int bodyPosY);

    private:
        void load_clothes();

};



#endif
