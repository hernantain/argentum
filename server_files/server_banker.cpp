#include <iostream>
#include "server_banker.h"

Banker::Banker(int16_t posX, int16_t posY) : 
    posX(posX),
    posY(posY) {}

int16_t Banker::get_pos_X() const {
    return posX;
}

int16_t Banker::get_pos_Y() const {
    return posY;
}
