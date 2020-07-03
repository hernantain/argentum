#include "server_magician.h"

#define MAGICIAN_ID 1


Magician::Magician(Json::Value &config) {
    this->id = MAGICIAN_ID;
    this->life_multiplier = config["magician"]["life_multiplier"].asFloat();
    this->mana_multiplier = config["magician"]["mana_multiplier"].asFloat();
    this->meditation_multiplier = config["magician"]["meditation_multiplier"].asFloat();
}
