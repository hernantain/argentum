#include "server_simple_bow.h"

SimpleBow::SimpleBow(Json::Value &config) : 
    Weapon(config["simpleBow"]["min_damage"].asInt(),
	       config["simpleBow"]["max_damage"].asInt()) {
        this->id = 16;
        this->name = "Arco Simple";
        this->ranged = true;
        this->magical = false;
    }
