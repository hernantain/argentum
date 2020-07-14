#include "server_inventory.h"
#include <iostream>

#define DROP_OFFSET_TOLERANCE 30
#define NOT_FOUND -1

Inventory::Inventory(int size) {
    this->max_size = size;
}

void Inventory::add_item(Item& item) {
    if (is_full()) return;
    int find_item = find(item.get_id());
    if (find_item != NOT_FOUND) {
        int16_t current_amount = items[find_item].get_amount();
        int16_t new_item_amount = item.get_amount();
        items[find_item].set_amount(current_amount + new_item_amount);
        return;
    }
    items.push_back(item);
}

Item Inventory::drop_item(uint8_t id) {
    Item drop_item;
    std::vector<Item> tmp;
    std::vector<Item>::iterator it = items.begin();
    for (; it != items.end(); ++it) {
        if (it->get_id() == id) {
            drop_item = (*it);
            std::cout << "Inventory::Deleting Item::" << drop_item.get_name() << std::endl;
            continue;
        }
        tmp.push_back(*it);
    }
    items.swap(tmp);
    return drop_item;
}

void Inventory::drop_items(int16_t posX, int16_t posY, std::vector<Item> &worldItems) {
    if (items.empty()) return;
    int16_t last_assignedX = posX - DROP_OFFSET_TOLERANCE;
    int16_t last_assignedY = posY - DROP_OFFSET_TOLERANCE;

    for (unsigned int i = 0; i < items.size(); i++) {
        items[i].set_posX(last_assignedX);
        items[i].set_posY(last_assignedY);

        last_assignedX += DROP_OFFSET_TOLERANCE;
        if(last_assignedX == posX + 2 * DROP_OFFSET_TOLERANCE) {
            last_assignedX -= DROP_OFFSET_TOLERANCE;
            last_assignedY += DROP_OFFSET_TOLERANCE;
        }
        if(last_assignedY == posY + 2 * DROP_OFFSET_TOLERANCE) {
            last_assignedX -= DROP_OFFSET_TOLERANCE;
            last_assignedY -= DROP_OFFSET_TOLERANCE;
        }
        worldItems.push_back(items[i]);
    }
    items.clear();
    std::cout << "InventorySize::ShouldBe0:: " << items.size() << std::endl;
}

bool Inventory::has(int16_t id) {
    std::vector<Item>::iterator it = items.begin();
    for (; it != items.end(); ++it) {
        if (it->get_id() == id) {
            std::cout << "Inventory::ItemFound" << std::endl;
            return true;
        }
    }
    return false;
}

int Inventory::find(int16_t id) {
    for (unsigned int i = 0; i < items.size(); i++) {
        if (items[i].get_id() == id) {
            std::cout << "Inventory::ItemFound" << std::endl;
            return i;
        }
    }
    return NOT_FOUND;
}

bool Inventory::is_full() {
    return items.size() == max_size;
}

unsigned int Inventory::size() {
    return items.size();
}
