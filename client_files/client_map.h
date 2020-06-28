#ifndef _CLIENT_MAP
#define _CLIENT_MAP

#include "SDL2/SDL.h"
#include "client_tile.h"
#include "client_tile_info.h"

#include <vector>

#include "../common_mapinfo.h"


class Map {
    SDL_Renderer* gRenderer;
    TileInfo tileInfo;
    std::vector<Tile> tilesFirstLayer;
    std::vector<Tile> tilesSecondLayer;

    public:
        Map(SDL_Renderer* gRenderer);

        void load(MapInfo &mapInfo);

        void render(SDL_Rect &camera);

        Map(Map&& other);
        Map& operator=(Map&& other);

        Map(const Map&) = delete;
        Map& operator=(const Map&) = delete;

};



#endif
