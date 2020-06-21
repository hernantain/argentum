#include "server_magician.h"

Magician::Magician(Json::Value &config) {
        this->life_multiplier = config["magician"]["life_multiplier"].asFloat();
        this->mana_multiplier = config["magician"]["mana_multiplier"].asFloat();
        this->meditation_multiplier = config["magician"]["meditation_multiplier"].asFloat();
    }
