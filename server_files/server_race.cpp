#include "server_race.h"

#define NO_DAMAGE 0

Race::Race(int initial_attributes) {
    this->strength = initial_attributes;
    this->agility = initial_attributes;
    this->intelligence = initial_attributes;
    this->constitution = initial_attributes;
}

int Race::get_strength() {
    return strength;
}

int Race::get_agility() {
    return agility;
}

int Race::get_intelligence() {
    return intelligence;
}

int Race::get_constitution() {
    return constitution;
}

float Race::get_life_multiplier() {
    return life_multiplier;
}

float Race::get_mana_multiplier() {
    return mana_multiplier;
}

int Race::get_recovery_factor() {
    return recovery_factor;
}

int Race::get_width() {
    return width;
}

int Race::get_height() {
    return height;
}

uint8_t Race::get_id() const {
    return id;
}
