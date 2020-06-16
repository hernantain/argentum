#include "server_hammer.h"

Hammer::Hammer(Json::Value &config) : 
    Weapon(config["hammer"]["min_damage"].asInt(),
	       config["hammer"]["max_damage"].asInt()) {
        this->id = 11;
        this->name = "Martillo";
    }
