#include "server_item.h"

Item::Item(int amount) {
    this->amount = amount;
    this->name = "An item";
}

std::string Item::get_name() {
    return name;
}