#include "server_citizen.h"

Citizen::Citizen(int16_t posX, int16_t posY) : 
    posX(posX),
    posY(posY) {}

int16_t Citizen::get_pos_X() const {
    return posX;
}

int16_t Citizen::get_pos_Y() const {
    return posY;
}
