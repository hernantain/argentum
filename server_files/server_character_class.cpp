#include "server_character_class.h"

CharacterClass::CharacterClass() {}

float CharacterClass::get_life_multiplier() {
    return life_multiplier;
}

float CharacterClass::get_mana_multiplier() {
    return mana_multiplier;
}

float CharacterClass::get_meditation_multiplier() {
    return meditation_multiplier;
}
