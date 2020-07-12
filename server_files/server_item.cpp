#include "server_item.h"

Item::Item() {}

std::string Item::get_name() {
    return name;
}

uint8_t Item::get_id() {
    return id;
}

int16_t Item::get_posX() {
    return id;
}

int16_t Item::get_posY() {
    return id;
}

int16_t Item::get_amount() {
    return amount;
}

void Item::set_amount(int16_t item_amount) {
    amount = item_amount;
}

void Item::set_posX(int16_t pos) {
    posX = pos;
}

void Item::set_posY(int16_t pos) {
    posY = pos;
}
