#include "server_inventory.h"
#include "server_os_error.h"
#include <iostream>

#define FULL_INVENTORY_ERROR "Error: inventario lleno!"
#define EMPTY_INVENTORY_ERROR "Error: inventario vacio!"

Inventory::Inventory(int size) {
    this->max_size = size;
}

void Inventory::add_item(Item& item) {
    if (is_full()) throw OSError(FULL_INVENTORY_ERROR);
    items.push_back(item);
    std::cout << "Item added" << std::endl;
}

Item Inventory::remove_item() {
    if (items.empty()) throw OSError(EMPTY_INVENTORY_ERROR);
    Item last_item = items.back();
    items.pop_back();
    std::cout << "Item removed" << std::endl;
    return last_item;
}

bool Inventory::is_full() {
    return items.size() == max_size;
}

unsigned int Inventory::size() {
    return items.size();
}
