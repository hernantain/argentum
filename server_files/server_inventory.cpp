#include "server_inventory.h"
#include <iostream>

Inventory::Inventory(int size) {
    this->max_size = size;
}

void Inventory::add_item(Item& item) {
    if (is_full()) return;
    items.push_back(item);
    std::cout << "Inventory::Added::" << item.get_id() << std::endl;
    std::cout << "Inventory::Size::" << items.size() << std::endl;
}

void Inventory::remove_item(Item &item) {
    if (items.empty()) return;
    // if (items.find(item) == items.end()) return;
    // // found
    // std::map<Item, int>::iterator it;
    // it = items.find(item);
    // items.erase(it);
}

void Inventory::drop_items(std::vector<Item> &worldItems) {
    if (items.empty()) return;

    // for i in items: popula el world items seteando posXposY, id

    items.clear();
    std::cout << "InventorySize:: " << items.size() << std::endl;
}

bool Inventory::has(Item& item) {
    // if (items.find(item) != items.end()) {
    //     std::cout << "Inventory::ItemFound" << std::endl;
    //     return true;
    // }
    return false;
}

bool Inventory::is_full() {
    return items.size() == max_size;
}

unsigned int Inventory::size() {
    return items.size();
}
