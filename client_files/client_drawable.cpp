
#include "client_player.h"
#include "client_drawable.h"


Drawable::Drawable( 
    int drawable_speed, 
    int16_t id) : id(id),
                velX(0),
                velY(0),
                frame(0),
                orientation(STANDING),
                drawable_speed(drawable_speed) {}



/**
 * 
 * SPRITE LOADING
 * 
 * Esto NO queda asi. Hay que generalizarlo para 
 * cada sprite una vez que sepamos que sprites vamos a usar
 * 
 * Por ahora queda hardcodeado para el sprite de testing que estoy usando.
 * 
 */



// void TallPlayer::loadBaculoSprites() {
//     this->baculoSprites[0].x = 0;
//     this->baculoSprites[0].y = 0;
//     this->baculoSprites[0].w = 23;
//     this->baculoSprites[0].h = 46;

//     this->baculoSprites[1].x = 23;
//     this->baculoSprites[1].y = 0;
//     this->baculoSprites[1].w = 23;
//     this->baculoSprites[1].h = 46;

//     this->baculoSprites[2].x = 47;
//     this->baculoSprites[2].y = 0;
//     this->baculoSprites[2].w = 23;
//     this->baculoSprites[2].h = 46;

//     this->baculoSprites[3].x = 90;
//     this->baculoSprites[3].y = 0;
//     this->baculoSprites[3].w = 23;
//     this->baculoSprites[3].h = 46;

//     this->baculoSprites[4].x = 114;
//     this->baculoSprites[4].y = 0;
//     this->baculoSprites[4].w = 23;
//     this->baculoSprites[4].h = 46;

//     this->baculoSprites[5].x = 0;
//     this->baculoSprites[5].y = 0;
//     this->baculoSprites[5].w = 23;
//     this->baculoSprites[5].h = 46;
// }