#include "server_item.h"

Item::Item() {}

std::string Item::get_name() {
    return name;
}

uint8_t Item::get_id() {
    return id;
}

int Item::get_posX() {
    return id;
}

int Item::get_posY() {
    return id;
}

int Item::get_amount() {
    return amount;
}

void Item::set_amount(int item_amount) {
    amount = item_amount;
}

void Item::set_posX(int pos) {
    posX = pos;
}

void Item::set_posY(int pos) {
    posY = pos;
}
