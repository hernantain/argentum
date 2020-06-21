#include "server_item.h"

Item::Item() {}

std::string Item::get_name() {
    return name;
}

int Item::get_id() {
    return id;
}