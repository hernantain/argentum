#ifndef _CLIENT_MAP
#define _CLIENT_MAP

#include "SDL2/SDL.h"
#include <vector>
#include <map>
#include "client_texture.h"

#include "../common_mapinfo.h"


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



class Map {
    SDL_Renderer* gRenderer;
    TileInfo tileInfo;
    std::vector<Tile> tiles;

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
