#include "server_paladin.h"

#define PALADIN_ID 3

Paladin::Paladin(Json::Value &config) {
    this->id = PALADIN_ID;
    this->life_multiplier = config["paladin"]["life_multiplier"].asFloat();
    this->mana_multiplier = config["paladin"]["mana_multiplier"].asFloat();
    this->meditation_multiplier = config["paladin"]["meditation_multiplier"]
    .asFloat();
}
