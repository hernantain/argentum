#include "server_item.h"

Item::Item() {
    this->name = "An item";
    this->id = 1;
}

std::string Item::get_name() {
    return name;
}

int Item::get_id() {
    return id;
}