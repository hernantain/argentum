#include "server_sword.h"

Sword::Sword(Json::Value &config) : 
    Weapon(config["sword"]["min_damage"].asInt(),
	       config["sword"]["max_damage"].asInt()) {
        this->id = 9;
        this->name = "Espada";
    }
