

#include "client_map.h"

#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>

#include <map>
#include <vector>
#include <string>
#include "client_texture.h"


Map::Map(SDL_Renderer* gRenderer) {
    this->gRenderer = gRenderer;
}


void Map::load(MapInfo &mapInfo) {
    
    std::vector<TileSetInfo> tileset_info = mapInfo.get_tileset_info();
    for (unsigned int i = 0; i < tileset_info.size(); ++i) {
        int tilecount = tileset_info[i].get_tilecount();

        if (tilecount == 1) {
            this->tileInfo.addTile();

        } else {
            int imagewidth = tileset_info[i].get_imagewidth();
            int width = imagewidth / 128;
            int x = 0;
            for (int i = 0; i < width; ++i) {
                this->tileInfo.addTile(x, 0);
                this->tileInfo.addTile(x, 128);
                x += 128;
            }
        }
        std::string imagePath = tileset_info[i].get_imagePath();
        int first_gid = tileset_info[i].get_first_gid();

        this->tileInfo.addTexture(first_gid, imagePath, gRenderer, tilecount);
    }   

    std::vector<int> layer1 = mapInfo.get_layer1();
    // std::vector<int> layer2 = mapInfo.get_layer2();
    int x = 0, y = 0;
    for (unsigned int i = 0; i < layer1.size(); ++i) {
        Tile tile(x, y, layer1[i]);
        this->tiles.push_back(tile);

        std::cout << "X: " << x << " Y: " << y << std::endl;

        x += 128;
        if( x >= 3200 ){
            x = 0;
            y += 128;
        }
    }

}




void Map::render(SDL_Rect &camera) {
    for (unsigned int i = 0; i < tiles.size(); ++i) {
        tiles[i].render(tileInfo, gRenderer, camera);
    }
}


Map::Map(Map&& other) {
    // std::cout << "Constructor por movimiento" << std::endl;
    this->gRenderer = other.gRenderer;
    this->tiles = std::move(other.tiles);
    this->tileInfo = std::move(other.tileInfo);
}

