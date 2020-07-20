#ifndef _CLIENT_MAP
#define _CLIENT_MAP

#include <vector>
#include "SDL2/SDL.h"
#include "client_tile.h"
#include "client_tile_info.h"
#include "client_banker.h"

#include "../common_files/common_mapinfo.h"


#define TILE_SIZE 128


class Map {
    SDL_Renderer* gRenderer;
    Banker banker;
    TileInfo tileInfo;
    std::vector<Tile> tilesFirstLayer;
    std::vector<Tile> tilesSecondLayer;

    public:
        Map(SDL_Renderer* gRenderer);

        void load(MapInfo &mapInfo);

        void renderFirstLayer(SDL_Rect &camera);
        void renderSecondLayer(SDL_Rect &camera);

        Map(Map&& other);
        Map& operator=(Map&& other);

        Map(const Map&) = delete;
        Map& operator=(const Map&) = delete;

};



#endif
