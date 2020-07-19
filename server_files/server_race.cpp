#include "server_race.h"

#define NO_DAMAGE 0

Race::Race(int initial_attributes) {
    this->strength = initial_attributes;
    this->agility = initial_attributes;
    this->intelligence = initial_attributes;
    this->constitution = initial_attributes;
}

int Race::get_strength() const {
    return strength;
}

int Race::get_agility() const {
    return agility;
}

int Race::get_intelligence() const {
    return intelligence;
}

int Race::get_constitution() const {
    return constitution;
}

float Race::get_life_multiplier() const {
    return life_multiplier;
}

float Race::get_mana_multiplier() const {
    return mana_multiplier;
}

int Race::get_recovery_factor() const {
    return recovery_factor;
}

int Race::get_width() const {
    return width;
}

int Race::get_height() const {
    return height;
}

uint8_t Race::get_id() const {
    return id;
}
