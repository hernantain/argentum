
#include "client_tile.h"


void Tile::render(TileInfo &tileInfo, SDL_Renderer* gRenderer, SDL_Rect &camera) {
    if (mType == 0)
        return;
        
    LTexture* texture = tileInfo.getTexture(mType);
    SDL_Rect box = tileInfo.getTileBox(mType - 1);
    texture->render(mBox.x - camera.x, mBox.y - camera.y, gRenderer, &box);
}


Tile::Tile( int x, int y, int tileType ) {
    mBox.x = x;
    mBox.y = y;

    mBox.w = 128;
    mBox.h = 128;

    mType = tileType;
}
