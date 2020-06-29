
#include "common_tileset_info.h"


TileSetInfo::TileSetInfo() {}

TileSetInfo::TileSetInfo(
    std::string imagePath, 
    int first_gid, 
    int tilecount, 
    int imagewidth,
    int imageheight) : imagePath(imagePath),
                        first_gid(first_gid),
                        tilecount(tilecount),
                        imagewidth(imagewidth),
                        imageheight(imageheight) {}



int TileSetInfo::get_first_gid() const {
    return this->first_gid;
}

int TileSetInfo::get_tilecount() const {
    return this->tilecount;
}

int TileSetInfo::get_imagewidth() const {
    return this->imagewidth;
}

int TileSetInfo::get_imageheight() const {
    return this->imageheight;
}

std::string TileSetInfo::get_imagePath() const {
    return this->imagePath;
}
