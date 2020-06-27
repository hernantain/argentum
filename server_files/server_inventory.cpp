#include "server_inventory.h"
#include "server_os_error.h"
#include <iostream>

#define FULL_INVENTORY_ERROR "Error: inventario lleno!"
#define EMPTY_INVENTORY_ERROR "Error: inventario vacio!"
#define NOT_FOUND_ERROR "Error: no se encuentra el item que busca!"

Inventory::Inventory(int size) {
    this->max_size = size;
}

void Inventory::add_item(Item& item) {
    if (is_full()) throw OSError(FULL_INVENTORY_ERROR);
    if (items.find(item) == items.end()) {
        // not found
        items[item] = 1;
        std::cout << "Item not found added" << std::endl;
    } else {
        // found
        items[item] += 1;
        std::cout << "Item found added" << std::endl;
    }
    std::cout << "Item amount: " << items[item] << std::endl;
}

void Inventory::remove_item(Item &item) {
    if (items.empty()) throw OSError(EMPTY_INVENTORY_ERROR);
    if (items.find(item) == items.end()) throw OSError(NOT_FOUND_ERROR);
    // found
    std::map<Item, int>::iterator it;
    it = items.find(item);
    // here send a message to the client
    items.erase(it);
    std::cout << "Items size should be Zero: " << items.size() << std::endl;
}

void Inventory::drop_items() {
    if (items.empty()) return;

    std::map<Item, int>::iterator it;
    for (it = items.begin(); it != items.end(); ++it) {
        Item current = it->first;
        std::cout << "Item name: " << current.get_name() << std::endl;
        // here send a message to the client
    }

    items.clear();
    std::cout << "Item size after dropping: " << items.size() << std::endl;
}

bool Inventory::has(Item& item) {
    if (items.find(item) != items.end()) {
        std::cout << "Item que tenemos en el inventario" << std::endl;
        return true;
    }
    return false;
}

bool Inventory::is_full() {
    return items.size() == max_size;
}

unsigned int Inventory::size() {
    return items.size();
}
