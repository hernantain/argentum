#ifndef _CLIENT_TILE
#define _CLIENT_TILE

#include "client_tile_info.h"
#include <SDL2/SDL.h>


class Tile {
    public:
		Tile( int x, int y, int tileType );

		void render(TileInfo &tileInfo, SDL_Renderer* gRenderer, SDL_Rect &camera);

		int getType();

		SDL_Rect getBox();

    private:
		SDL_Rect mBox;

		int mType;
};



#endif
