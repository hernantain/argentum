

#include <fstream>
#include <jsoncpp/json/json.h>

#include "common_mapinfo.h"

MapInfo::MapInfo() {}


void MapInfo::loadCollisionInfo(CollisionInfo &collisionInfo, Json::Value &tileJson, int &first_tile_gid) {

    const Json::Value& tiles = tileJson["tiles"];
    for (unsigned int i = 0; i < tiles.size(); ++i) {
        CollisionTile collisionTile;
        collisionTile.x = tiles[i]["objectgroup"]["objects"][0]["x"].asInt();
        collisionTile.y = tiles[i]["objectgroup"]["objects"][0]["y"].asInt() ;
        collisionTile.w = tiles[i]["objectgroup"]["objects"][0]["width"].asInt();
        collisionTile.h = tiles[i]["objectgroup"]["objects"][0]["height"].asInt();
        collisionTile.id = tiles[i]["id"].asInt() + first_tile_gid;
        collisionInfo.tiles.push_back(collisionTile);
    }
}



CollisionInfo MapInfo::load() {

    std::ifstream map("maps/argentum.json");
    Json::Reader reader;
    Json::Value obj, tileJson;
    reader.parse(map, obj); 

    this->tile_width = obj["tilewidth"].asInt();
    this->tile_height = obj["tileheight"].asInt();
    this->map_width = obj["width"].asInt();
    this->map_height = obj["height"].asInt();

    CollisionInfo collisionInfo(tile_width, tile_height, map_width, map_height);

    const Json::Value& tilesets = obj["tilesets"]; 
    const Json::Value& layers = obj["layers"];
    const Json::Value& grounds = layers[0]["data"];
    const Json::Value& trees = layers[1]["data"];
    const Json::Value& bankersPos = obj["bankers"];
    const Json::Value& priestsPos = obj["priests"];
    
    this->banker.push_back(bankersPos[0]["posX"].asInt());
    collisionInfo.banker.push_back(bankersPos[0]["posX"].asInt());
    
    this->priest.push_back(priestsPos[0]["posX"].asInt());
    collisionInfo.priest.push_back(priestsPos[0]["posX"].asInt());
    
    this->banker.push_back(bankersPos[0]["posY"].asInt());
    collisionInfo.banker.push_back(bankersPos[0]["posY"].asInt());
    
    this->priest.push_back(priestsPos[0]["posY"].asInt());
    collisionInfo.priest.push_back(priestsPos[0]["posY"].asInt());

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
        collisionInfo.layer1.push_back(grounds[i].asInt());
    }


    for (unsigned int i = 0; i < trees.size(); ++i) {
        this->layer2.push_back(trees[i].asInt());
        collisionInfo.layer2.push_back(trees[i].asInt());
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


int MapInfo::get_banker_posX() const {
    return banker[0];
}


int MapInfo::get_banker_posY() const {
    return banker[1];
}

int MapInfo::get_priest_posX() const {
    return priest[0];
}


int MapInfo::get_priest_posY() const {
    return priest[1];
}


