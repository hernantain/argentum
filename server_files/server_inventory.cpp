#include "server_inventory.h"
#include <iostream>

#define DROP_OFFSET_TOLERANCE 20

Inventory::Inventory(int size) {
    this->max_size = size;
}

void Inventory::add_item(Item& item) {
    if (is_full()) return;
    items.push_back(item);
    std::cout << "Inventory::Added::" << item.get_name() << std::endl;
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

    // std::cout << "MyPosX::: " << posX << std::endl;
    // std::cout << "MyPosY::: " << posY << std::endl;
    for (unsigned int i = 0; i < items.size(); i++) {
        // std::cout << "ItemDropPosX::: " << last_assignedX << std::endl;
        // std::cout << "ItemDropPosY::: " << last_assignedY << std::endl;
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

bool Inventory::is_full() {
    return items.size() == max_size;
}

unsigned int Inventory::size() {
    return items.size();
}
