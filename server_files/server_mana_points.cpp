#include "server_mana_points.h"

#define INITIAL_LEVEL 1

ManaPoints::ManaPoints(int intelligence, float class_multiplier, float race_multiplier) {
    this->intelligence = intelligence;
    this->class_multiplier = class_multiplier;
    this->race_multiplier = race_multiplier;
    set_new_max(INITIAL_LEVEL);
}

void ManaPoints::subtract(int mana_points) {
    if (current_mana >= mana_points)
        current_mana -= mana_points;
    else
        current_mana = 0;
}

void ManaPoints::add(int mana_points) {
    if (current_mana == max_mana) return;
    current_mana += mana_points;
    if (current_mana >= max_mana) current_mana = max_mana;
}

int ManaPoints::current() {
    return current_mana;
}

int ManaPoints::max(){
    return max_mana;
}

void ManaPoints::set_new_max(int level) {
    int new_max_mana = intelligence * class_multiplier * race_multiplier * level;
    this->current_mana = new_max_mana;
    this->max_mana = new_max_mana;
}
