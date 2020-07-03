#include "server_cleric.h"

#define CLERIC_ID 2

Cleric::Cleric(Json::Value &config) {
    this->id = CLERIC_ID;
    this->life_multiplier = config["cleric"]["life_multiplier"].asFloat();
    this->mana_multiplier = config["cleric"]["mana_multiplier"].asFloat();
    this->meditation_multiplier = config["cleric"]["meditation_multiplier"].asFloat();
}
