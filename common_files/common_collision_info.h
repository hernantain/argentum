#ifndef _COMMON_COLLISION_INFO
#define _COMMON_COLLISION_INFO

#include <vector>
#include <map>

struct CollisionTile {

    int x, y, w, h, id;

    CollisionTile();

    // CollisionTile(int x, int y, int w, int h);

};



class CollisionInfo {
    int tilewidth, tileheight;
    int mapwidth, mapheight;

    public:
        std::vector<int> layer1;
        std::vector<int> layer2;
        // std::map<int, CollisionTile> tiles;
        std::vector<CollisionTile> tiles;
    
        CollisionInfo(int tilewidth, int tileheight, int mapwidth, int mapheight);

        int get_map_width() const;
        int get_map_height() const;
        int get_tile_width() const;
        int get_tile_height() const;
        int find(int tileId) const;

        CollisionInfo(CollisionInfo&& other);
        CollisionInfo& operator=(CollisionInfo&& other);

        CollisionInfo(const CollisionInfo&) = delete;
        CollisionInfo& operator=(const CollisionInfo&) = delete;
};



#endif

