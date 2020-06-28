#ifndef _SERVER_COLLISION_INFO
#define _SERVER_COLLISION_INFO

#include <vector>
#include <map>

struct CollisionTile {

    int x, y, w, h;

    CollisionTile();


};



class CollisionInfo {

    public:
        std::vector<int> layer;
        std::map<int, CollisionTile> tiles;

        CollisionInfo();

        CollisionInfo(CollisionInfo&& other);
        CollisionInfo& operator=(CollisionInfo&& other);

        CollisionInfo(const CollisionInfo&) = delete;
        CollisionInfo& operator=(const CollisionInfo&) = delete;

};



#endif

