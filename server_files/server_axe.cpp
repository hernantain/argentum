#include "server_axe.h"

Axe::Axe(Json::Value &config) : 
    Weapon(config["axe"]["min_damage"].asInt(),
	       config["axe"]["max_damage"].asInt()) {
        this->id = 10;
        this->name = "Hacha";
        this->ranged = false;
        this->magical = false;
    }
