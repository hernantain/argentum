#include "server_warrior.h"

Warrior::Warrior(Json::Value &config) {
        this->life_multiplier = config["warrior"]["life_multiplier"].asFloat();
        this->mana_multiplier = config["warrior"]["mana_multiplier"].asFloat();
        this->meditation_multiplier = config["warrior"]["meditation_multiplier"].asFloat();
    }
