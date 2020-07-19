
#include <iostream>
#include "client_tile_info.h"



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
            this->textures.insert(std::pair<int, LTexture*> (i, texture));
    }
}

SDL_Rect TileInfo::getTileBox(int i) {
    return this->tiles[i];
}

LTexture* TileInfo::getTexture(int i) {
    return this->textures[i];
}


TileInfo::~TileInfo() {
    // std::cout << "Destroying TILE INFO TEXTURES" << std::endl;
    // std::map<int, LTexture*>::iterator itr;
    // for (itr = textures.begin(); itr != textures.end(); ++itr)  
    //     itr->second->free();
}
