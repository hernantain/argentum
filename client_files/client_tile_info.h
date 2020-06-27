#ifndef _CLIENT_TILE_INFO
#define _CLIENT_TILE_INFO


#include <SDL2/SDL.h>
#include <map>
#include <vector>

#include "client_texture.h"


class TileInfo {

    std::vector<SDL_Rect> tiles;
    std::map<int, LTexture*> textures;

    public:
        TileInfo();

        void addTile(int x = 0, int y = 0);

        void addTexture(int id, std::string image, SDL_Renderer* gRenderer, int numTiles=1);

        LTexture* getTexture(int i);
        SDL_Rect getTileBox(int i);
};



#endif
