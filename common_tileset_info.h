#ifndef _TILESET_INFO
#define _TILESET_INFO

#include <string>
#include <msgpack.hpp>


class TileSetInfo {

    std::string imagePath;
    int first_gid, tilecount, imagewidth;

    public:
        TileSetInfo();

        TileSetInfo(std::string imagePath, int first_gid, int tilecount, int imagewidth);

        int get_first_gid() const;
        int get_tilecount() const;
        int get_imagewidth() const;
        std::string get_imagePath() const;


    MSGPACK_DEFINE(imagePath, first_gid, tilecount, imagewidth)

};


#endif
