#ifndef _TILESET_INFO
#define _TILESET_INFO

#include <string>
#include <msgpack.hpp>


class TileSetInfo {

    std::string imagePath;
    int first_gid, tilecount, imagewidth, imageheight;

    public:
        TileSetInfo();

        TileSetInfo(std::string imagePath, int first_gid, int tilecount, int imagewidth, int imageheight);

        int get_first_gid() const;
        int get_tilecount() const;
        int get_imagewidth() const;
        int get_imageheight() const;
        std::string get_imagePath() const;


    MSGPACK_DEFINE(imagePath, first_gid, tilecount, imagewidth, imageheight)

};


#endif
