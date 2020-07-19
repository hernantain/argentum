
#include "client_item.h"


Item::Item(
    uint8_t id, 
    int16_t posX, 
    int16_t posY, 
    int16_t amount) : id(id), posX(posX), posY(posY), amount(amount) {}



uint8_t Item::get_id() const {
    return this->id;
}


int16_t Item::get_posX() const {
    return this->posX;
}


int16_t Item::get_posY() const {
    return this->posY;
}


void Item::set_posX(int16_t posX) {
    this->posX = posX;
}


void Item::set_posY(int16_t posY) {
    this->posY = posY;
}

void Item::add_amount() {
    this->amount++;
}


Item::~Item() {}
