
#include "client_map.h"

#include <fstream>
#include <jsoncpp/json/json.h>

#include <map>
#include <vector>
#include <string>
#include "client_texture.h"


Map::Map(SDL_Renderer* gRenderer) : banker(gRenderer), priest(gRenderer) {
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
            int imageheight = tileset_info[i].get_imageheight();
            int width = imagewidth / TILE_SIZE;
            int height = imageheight / TILE_SIZE;
            int y = 0, x;
            for (int i = 0; i < height; ++i) {
                x = 0;
                for (int j = 0; j < width; ++j) {
                    this->tileInfo.addTile(x, y);
                    x += TILE_SIZE;
                }
                y += TILE_SIZE;
            }
        }
        std::string imagePath = tileset_info[i].get_imagePath();
        int first_gid = tileset_info[i].get_first_gid();

        this->tileInfo.addTexture(first_gid, imagePath, gRenderer, tilecount);
    }   
  
    std::vector<int> layer1 = mapInfo.get_layer1();
    std::vector<int> layer2 = mapInfo.get_layer2();

    int x = 0, y = 0;
    for (unsigned int i = 0; i < layer1.size(); ++i) {
        Tile tile1(x, y, layer1[i]);
        Tile tile2(x, y, layer2[i]);
        this->tilesFirstLayer.push_back(tile1);
        this->tilesSecondLayer.push_back(tile2);
        x += TILE_SIZE;
        if( x >= 3200 ){
            x = 0;
            y += TILE_SIZE;
        }
    }

    banker.load(mapInfo.get_banker_posX(), mapInfo.get_banker_posY());
    priest.load(mapInfo.get_priest_posX(), mapInfo.get_priest_posY());
}



void Map::renderFirstLayer(SDL_Rect &camera) {
    for (unsigned int i = 0; i < tilesFirstLayer.size(); ++i) 
        tilesFirstLayer[i].render(tileInfo, gRenderer, camera);
}


void Map::renderSecondLayer(SDL_Rect &camera) {
    banker.render(camera);
    priest.render(camera);
    for (unsigned int i = 0; i < tilesSecondLayer.size(); ++i) 
        tilesSecondLayer[i].render(tileInfo, gRenderer, camera);

}


Map::Map(Map&& other) : banker(other.gRenderer), priest(other.gRenderer) {
    this->gRenderer = other.gRenderer;
    this->banker = std::move(other.banker);
    this->priest = std::move(other.priest);
    this->tilesFirstLayer = std::move(other.tilesFirstLayer);
    this->tilesSecondLayer = std::move(other.tilesSecondLayer);
    this->tileInfo = std::move(other.tileInfo);
}
