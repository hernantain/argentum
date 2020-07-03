#include "server_warrior.h"

#define WARRIOR_ID 4

Warrior::Warrior(Json::Value &config) {
    this->id = WARRIOR_ID;
    this->life_multiplier = config["warrior"]["life_multiplier"].asFloat();
    this->mana_multiplier = config["warrior"]["mana_multiplier"].asFloat();
    this->meditation_multiplier = config["warrior"]["meditation_multiplier"].asFloat();
}
