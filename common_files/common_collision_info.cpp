
#include <iostream>
#include "common_collision_info.h"


CollisionInfo::CollisionInfo(int tilewidth, int tileheight, int mapwidth, int mapheight) {
    this->tilewidth = tilewidth;
    this->tileheight = tileheight;
    this->mapwidth = mapwidth;
    this->mapheight = mapheight;
}


CollisionTile::CollisionTile() {}

CollisionInfo::CollisionInfo(CollisionInfo&& other) {
    this->tilewidth = std::move(other.tilewidth);
    this->tileheight = std::move(other.tileheight);
    this->mapwidth = std::move(other.mapwidth);
    this->mapheight = std::move(other.mapheight); 
    this->layer1 = std::move(other.layer1);
    this->layer2 = std::move(other.layer2);
    this->banker = std::move(other.banker);
    this->priest = std::move(other.priest);
    this->tiles = std::move(other.tiles);
}


int CollisionInfo::get_map_width() const {
    return mapwidth * tilewidth;
}


int CollisionInfo::get_map_height() const {
    return mapheight * tileheight; 
}


int CollisionInfo::get_tile_width() const {
    return tilewidth;
}

int CollisionInfo::get_tile_height() const {
    return tileheight;
}

int CollisionInfo::find(int tileId) const {
    for (unsigned int i = 0; i < tiles.size(); ++i) {
        if (tiles[i].id == tileId)
            return i;
    }

    return -1;
}


int CollisionInfo::get_banker_posX() const {
    return banker[0];
}


int CollisionInfo::get_banker_posY() const {
    return banker[1];
}


int CollisionInfo::get_priest_posX() const {
    return priest[0];
}


int CollisionInfo::get_priest_posY() const {
    return priest[1];
}


