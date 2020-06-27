#ifndef _CLIENT_TALL_PLAYER
#define _CLIENT_TALL_PLAYER

#include <SDL2/SDL.h>
#include "client_player.h"


class TallPlayer: public Player {
    
    const int PLAYER_WIDTH = 23;
    const int PLAYER_HEIGHT = 42;

    public:
        TallPlayer(SDL_Renderer* gRenderer, const char* head_path);

    private:
        void load_clothes(SDL_Renderer* gRenderer);

};



#endif

