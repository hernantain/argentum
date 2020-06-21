#include "server_cleric.h"

Cleric::Cleric(Json::Value &config) {
        this->life_multiplier = config["cleric"]["life_multiplier"].asFloat();
        this->mana_multiplier = config["cleric"]["mana_multiplier"].asFloat();
        this->meditation_multiplier = config["cleric"]["meditation_multiplier"].asFloat();
    }
