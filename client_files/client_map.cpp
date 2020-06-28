

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
            int y = 0;
            for (int i = 0; i < width; ++i) {
                this->tileInfo.addTile(0, y);
                this->tileInfo.addTile(128, y);
                y += 128;
            }
        }
        std::string imagePath = tileset_info[i].get_imagePath();
        int first_gid = tileset_info[i].get_first_gid();

        this->tileInfo.addTexture(first_gid, imagePath, gRenderer, tilecount);
    }   

    std::map<int, LTexture*>::iterator itr;  
    for (itr = tileInfo.textures.begin(); itr != tileInfo.textures.end(); ++itr) { 
        std::cout << '\t' << itr->first << '\n'; 
    } 
    std::cout << std::endl; 
  


    std::vector<int> layer1 = mapInfo.get_layer1();
    std::vector<int> layer2 = mapInfo.get_layer2();

    for (unsigned int i = 0; i < layer2.size(); ++i) {
        std::cout << layer2[i];
    }
    std::cout << std::endl;

    int x = 0, y = 0;
    for (unsigned int i = 0; i < layer1.size(); ++i) {
        Tile tile1(x, y, layer1[i]);
        Tile tile2(x, y, layer2[i]);
        this->tilesFirstLayer.push_back(tile1);
        this->tilesSecondLayer.push_back(tile2);

        std::cout << "X: " << x << " Y: " << y << std::endl;

        x += 128;
        if( x >= 3200 ){
            x = 0;
            y += 128;
        }
    }



}


void Map::render(SDL_Rect &camera) {
    for (unsigned int i = 0; i < tilesFirstLayer.size(); ++i) {
        tilesFirstLayer[i].render(tileInfo, gRenderer, camera);
        tilesSecondLayer[i].render(tileInfo, gRenderer, camera);
    }
}



Map::Map(Map&& other) {
    // std::cout << "Constructor por movimiento" << std::endl;
    this->gRenderer = other.gRenderer;
    this->tilesFirstLayer = std::move(other.tilesFirstLayer);
    this->tilesSecondLayer = std::move(other.tilesSecondLayer);
    this->tileInfo = std::move(other.tileInfo);
}

