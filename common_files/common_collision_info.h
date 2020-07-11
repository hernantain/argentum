#ifndef _COMMON_COLLISION_INFO
#define _COMMON_COLLISION_INFO

#include <vector>
#include <map>

struct CollisionTile {

    int x, y, w, h;

    CollisionTile();

};



class CollisionInfo {
    int tilewidth, tileheight;
    int mapwidth, mapheight;

    public:
        std::vector<int> layer1;
        std::vector<int> layer2;
        std::map<int, CollisionTile> tiles;

        CollisionInfo(int tilewidth, int tileheight, int mapwidth, int mapheight);

        int get_map_width() const;
        int get_map_height() const;
        int get_tile_width() const;
        int get_tile_height() const;

        CollisionInfo(CollisionInfo&& other);
        CollisionInfo& operator=(CollisionInfo&& other);

        CollisionInfo(const CollisionInfo&) = delete;
        CollisionInfo& operator=(const CollisionInfo&) = delete;
};



#endif

