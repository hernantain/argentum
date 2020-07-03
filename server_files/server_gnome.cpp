#include "server_gnome.h"

#define GNOME_ID 4

Gnome::Gnome(Json::Value &config) : 
    Race(config["initialAttributes"].asInt()) {
        this->id = GNOME_ID;
        this->strength -= config["gnome"]["strength_modifier"].asInt();
        this->agility += config["gnome"]["agility_modifier"].asInt();
        this->intelligence += config["gnome"]["intelligence_modifier"].asInt();

        this->life_multiplier = config["gnome"]["life_multiplier"].asFloat();
        this->mana_multiplier = config["gnome"]["mana_multiplier"].asFloat();
        this->recovery_multiplier = config["gnome"]["recovery_multiplier"].asFloat();
    }
