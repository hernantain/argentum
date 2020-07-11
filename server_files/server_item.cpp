#include "server_item.h"

Item::Item() {}

std::string Item::get_name() {
    return name;
}

uint8_t Item::get_id() {
    return id;
}