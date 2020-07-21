#include "server_inventory.h"

#define DROP_OFFSET_TOLERANCE 30
#define NOT_FOUND -1
#define DEFAULT_EQUIPMENT 0

Inventory::Inventory(int size) {
    this->max_size = size;
}

bool Inventory::add_item(Item& item) {
    if (is_full()) return false;
    int find_item = find(item.get_id());
    if (find_item != NOT_FOUND) {
        int16_t current_amount = items[find_item].get_amount();
        int16_t new_item_amount = item.get_amount();
        items[find_item].set_amount(current_amount + new_item_amount);
        return true;
    }
    items.push_back(item);
    return true;
}

void Inventory::remove_item(const uint8_t id) {
    int position = find(id);
    int16_t item_amount = items[position].get_amount();
    if (item_amount > 1) 
        items[position].set_amount(item_amount--);
    else 
        drop_item(id);
}

Item Inventory::drop_item(const uint8_t id) {
    Item drop_item;
    std::vector<Item> tmp;
    std::vector<Item>::iterator it = items.begin();
    for (; it != items.end(); ++it) {
        if (it->get_id() == id) {
            drop_item = (*it);
            continue;
        }
        tmp.push_back(*it);
    }
    items.swap(tmp);
    return drop_item;
}

void Inventory::drop_items(int16_t posX, int16_t posY, int gold, std::vector<Item> &worldItems) {
    if (items.empty() && gold == 0) return;
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
    drop_gold(posX, posY, gold, worldItems);
}

void Inventory::drop_gold(int16_t posX, int16_t posY, int gold, std::vector<Item> &worldItems) {
    if (gold > 0) {
        Gold to_drop(gold);
        to_drop.set_posX(posX - 2 * DROP_OFFSET_TOLERANCE);
        to_drop.set_posY(posY - 2 * DROP_OFFSET_TOLERANCE);
        worldItems.push_back(to_drop);
    }
}

bool Inventory::has(const int16_t id) {
    if (id == DEFAULT_EQUIPMENT) return true;
    std::vector<Item>::iterator it = items.begin();
    for (; it != items.end(); ++it) {
        if (it->get_id() == id) 
            return true;
    }
    return false;
}

int Inventory::find(const int16_t id) const {
    for (unsigned int i = 0; i < items.size(); i++) {
        if (items[i].get_id() == id) 
            return i;
    }
    return NOT_FOUND;
}

bool Inventory::is_full() const {
    return items.size() == max_size;
}

unsigned int Inventory::size() const {
    return items.size();
}
