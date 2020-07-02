
#include "common_collision_info.h"


CollisionInfo::CollisionInfo() {}



CollisionTile::CollisionTile() {}




#include <iostream>


CollisionInfo::CollisionInfo(CollisionInfo&& other) {
    // std::cout << "Construyendo por movement" << std::endl;
    this->layer = std::move(other.layer);
    this->tiles = std::move(other.tiles);
}

