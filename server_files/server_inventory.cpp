#include "server_inventory.h"
#include <iostream>

Inventory::Inventory(int size) {
    this->max_size = size;
}

void Inventory::add_item(Item& item) {
    if (is_full()) return;
    if (items.find(item) == items.end()) {
        items[item] = 1;
        std::cout << "Inventory::NewItemAdded::" << item.get_name() << std::endl;
    } else {
        items[item] += 1;
        std::cout << "Inventory::ItemWeAlreadyHadAdded::" << item.get_name() << std::endl;
    }
    std::cout << "Inventory::ItemAddedSize::" << items[item] << std::endl;
}

void Inventory::remove_item(Item &item) {
    if (items.empty()) return;
    if (items.find(item) == items.end()) return;
    // found
    std::map<Item, int>::iterator it;
    it = items.find(item);
    items.erase(it);
}

void Inventory::drop_items() {
    if (items.empty()) return;

    std::map<Item, int>::iterator it;
    for (it = items.begin(); it != items.end(); ++it) {
        Item current = it->first;
        std::cout << "DroppingItem:: " << current.get_name() << std::endl;
    }

    items.clear();
    std::cout << "InventorySize:: " << items.size() << std::endl;
}

bool Inventory::has(Item& item) {
    if (items.find(item) != items.end()) {
        std::cout << "Inventory::ItemFound" << std::endl;
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
