

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


TileInfo::TileInfo() {}

void TileInfo::addTile(int x, int y) {
    SDL_Rect tile = {x, y, 128, 128 };
    this->tiles.push_back(tile);
}


void TileInfo::addTexture(int id, std::string image, SDL_Renderer* gRenderer, int numTiles) {
    LTexture* texture = new LTexture();
    texture->loadFromFile(image, gRenderer);
    
    if (numTiles == 1) {
        this->textures.insert(std::pair<int, LTexture*> (id, texture));
    } else {
        for (int i = id; i < id+numTiles; ++i) 
            this->textures.insert(std::pair<int, LTexture*> (id, texture));
    }
}

SDL_Rect TileInfo::getTileBox(int i) {
    return this->tiles[i];
}

LTexture* TileInfo::getTexture(int i) {
    return this->textures[i];
}


void Tile::render(TileInfo &tileInfo, SDL_Renderer* gRenderer, SDL_Rect &camera) {
    LTexture* texture = tileInfo.getTexture(mType);
    SDL_Rect box = tileInfo.getTileBox(mType - 1);
    texture->render(mBox.x - camera.x, mBox.y - camera.y, gRenderer, &box);
}


Tile::Tile( int x, int y, int tileType ) {
    mBox.x = x;
    mBox.y = y;

    mBox.w = 128;
    mBox.h = 128;

    mType = tileType;
}


void Map::load(MapInfo &mapInfo) {
    
    std::vector<TileInfos> tile_info = mapInfo.get_tile_info();
    for (unsigned int i = 0; i < tile_info.size(); ++i) {
        int tilecount = tile_info[i].get_tilecount();

        if (tilecount == 1) {
            this->tileInfo.addTile();

        } else {
            int imagewidth = tile_info[i].get_imagewidth();
            int width = imagewidth / 128;
            int x = 0;
            for (int i = 0; i < width; ++i) {
                this->tileInfo.addTile(x, 0);
                this->tileInfo.addTile(x, 128);
                x += 128;
            }
        }
        std::string imagePath = tile_info[i].get_imagePath();
        int first_gid = tile_info[i].get_first_gid();

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

