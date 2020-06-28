#include <math.h>
#include <iostream>
#include <stdio.h>
#include "server_npc.h"

#define NO_LIFE 0
#define INITIAL_GOLD 0
#define INITIAL_LEVEL 1

NPC::NPC(size_t id, Json::Value &config) : config(config) {
    this->id = id;
    this->alive = true;
}

int NPC::get_id() {
    return id;
}

int NPC::get_level() {
    return level;
}

int NPC::get_life() {
    return life;
}

void NPC::drop() {
    int nothing_percentage = config["npc"]["nothing_drop_probability"].asFloat() * 100;
    int gold_percentage = config["npc"]["gold_drop_probability"].asFloat() * 100;
    int potion_percentage = config["npc"]["potion_drop_probability"].asFloat() * 100;
    int item_percentage = config["npc"]["another_item_probability"].asFloat() * 100;

    srand (time(NULL));
    int drop_chances = rand() % 100 + 1;
    std::cout << "Drop chances: " << drop_chances << std::endl;
    if (drop_chances <= nothing_percentage) return;
    if (drop_chances <= nothing_percentage + gold_percentage) {
        // send message of drop gold
        // calculate how much gold to drop
        return gold_drop;
    }
    if (drop_chances <= nothing_percentage + gold_percentage + potion_percentage) {
        // send message of drop potion
        return potion_drop;
    }
    if (drop_chances <= nothing_percentage + gold_percentage + potion_percentage + item_percentage) {
        // send message of drop item
        return item_drop;
    }
}