#ifndef _MAP_INFO
#define _MAP_INFO

#include <string>
#include <vector>
#include <msgpack.hpp>

#include <jsoncpp/json/json.h>
#include "common_tileset_info.h"
#include "common_collision_info.h"

class MapInfo {

    int tile_width, tile_height;
    int map_width, map_height;
    std::vector<int> layer1;
    std::vector<int> layer2;
    std::vector<int> banker;
    std::vector<TileSetInfo> tileSetInfo;

    public:
        MapInfo();

        CollisionInfo load();

        std::vector<TileSetInfo> get_tileset_info() const;
        std::vector<int> get_layer1() const;
        std::vector<int> get_layer2() const;
        int get_banker_posX() const;
        int get_banker_posY() const;
        void loadCollisionInfo(CollisionInfo &collisionInfo, Json::Value &tileJson, int &first_tile_gid);


    MSGPACK_DEFINE(tile_width, tile_height, map_width, map_height, layer1, layer2, banker, tileSetInfo)

};


#endif
