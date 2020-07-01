#include "server_mana_potion.h"

ManaPotion::ManaPotion(Json::Value &config) : 
    Potion(config["manaPotion"]["recovery"].asInt()) {
        this->id = config["manaPotion"]["id"].asInt();
        this->name = "Poción de mana";
    }
