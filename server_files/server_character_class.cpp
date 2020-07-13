#include "server_character_class.h"

CharacterClass::CharacterClass() {}

uint8_t CharacterClass::get_id() const {
    return this->id;
}

float CharacterClass::get_life_multiplier() const {
    return life_multiplier;
}

float CharacterClass::get_mana_multiplier() const {
    return mana_multiplier;
}

float CharacterClass::get_meditation_multiplier() const {
    return meditation_multiplier;
}
