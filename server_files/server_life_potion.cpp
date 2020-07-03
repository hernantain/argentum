#include "server_life_potion.h"

LifePotion::LifePotion(Json::Value &config) : 
    Potion(config["lifePotion"]["recovery"].asInt()) {
        this->id = config["lifePotion"]["id"].asInt();
        this->name = "Poción de vida";
    }
