
#include "common_collision_info.h"


CollisionInfo::CollisionInfo() {}



CollisionTile::CollisionTile() {}


CollisionInfo::CollisionInfo(CollisionInfo&& other) {
    this->layer = std::move(other.layer);
    this->tiles = std::move(other.tiles);
}

