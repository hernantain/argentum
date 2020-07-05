

#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>

#include "common_mapinfo.h"

MapInfo::MapInfo() {}


void MapInfo::loadCollisionInfo(CollisionInfo &collisionInfo, Json::Value &tileJson, int &first_tile_gid) {

    const Json::Value& tiles = tileJson["tiles"];
    int id;
    for (unsigned int i = 0; i < tiles.size(); ++i) {
        CollisionTile collisionTile;
        collisionTile.x = tiles[i]["objectgroup"]["objects"][0]["x"].asInt();
        collisionTile.y = tiles[i]["objectgroup"]["objects"][0]["y"].asInt() ;
        collisionTile.w = tiles[i]["objectgroup"]["objects"][0]["width"].asInt();
        collisionTile.h = tiles[i]["objectgroup"]["objects"][0]["height"].asInt();
        id = tiles[i]["id"].asInt();
        collisionInfo.tiles.insert(std::pair<int, CollisionTile> (id+first_tile_gid, collisionTile));
    }
}



CollisionInfo MapInfo::load() {

    CollisionInfo collisionInfo;

    std::ifstream map("argentum.json");
    Json::Reader reader;
    Json::Value obj, tileJson;
    reader.parse(map, obj); 
    const Json::Value& tilesets = obj["tilesets"]; 
    const Json::Value& layers = obj["layers"];
    const Json::Value& grounds = layers[0]["data"];
    const Json::Value& trees = layers[1]["data"];

    std::string source;
    for (unsigned int i = 0; i < tilesets.size(); ++i) {
        source = tilesets[i]["source"].asString();
        std::ifstream tileInfo(source);
        reader.parse(tileInfo, tileJson);

        std::string imagePath = tileJson["image"].asString();
        int first_gid = tilesets[i]["firstgid"].asInt();
        int tilecount = tileJson["tilecount"].asInt();
        int imagewidth = tileJson["imagewidth"].asInt();
        int imageheight = tileJson["imageheight"].asInt();
 
        if (!tileJson["tiles"].isNull()) 
            this->loadCollisionInfo(collisionInfo, tileJson, first_gid);


        TileSetInfo tile(imagePath, first_gid, tilecount, imagewidth, imageheight);
        this->tileSetInfo.push_back(tile);
    }

    for (unsigned int i = 0; i < grounds.size(); ++i) {
        this->layer1.push_back(grounds[i].asInt());
    }


    for (unsigned int i = 0; i < trees.size(); ++i) {
        this->layer2.push_back(trees[i].asInt());
        collisionInfo.layer.push_back(trees[i].asInt());
    }

    return std::move(collisionInfo);
}


std::vector<TileSetInfo> MapInfo::get_tileset_info() const {
    return this->tileSetInfo;
}

std::vector<int> MapInfo::get_layer1() const {
    return this->layer1;
}


std::vector<int> MapInfo::get_layer2() const {
    return this->layer2;
}
