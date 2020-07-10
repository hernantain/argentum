#include "server_human.h"

#define HUMAN_ID 1

Human::Human(Json::Value &config) : 
    Race(config["initialAttributes"].asInt()) {
        this->id = HUMAN_ID;
        this->strength += config["human"]["strength_modifier"].asInt();
        this->agility += config["human"]["agility_modifier"].asInt();
        this->constitution += config["human"]["constitution_modifier"].asInt();

        this->life_multiplier = config["human"]["life_multiplier"].asFloat();
        this->mana_multiplier = config["human"]["mana_multiplier"].asFloat();
        this->recovery_factor = config["human"]["recovery_factor"].asFloat();
    }
