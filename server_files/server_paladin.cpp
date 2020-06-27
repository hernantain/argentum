#include "server_paladin.h"

Paladin::Paladin(Json::Value &config) {
        this->life_multiplier = config["paladin"]["life_multiplier"].asFloat();
        this->mana_multiplier = config["paladin"]["mana_multiplier"].asFloat();
        this->meditation_multiplier = config["paladin"]["meditation_multiplier"]
        .asFloat();
    }
