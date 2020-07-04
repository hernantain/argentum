#include "server_compound_bow.h"

CompoundBow::CompoundBow(Json::Value &config) : 
    Weapon(config["compoundBow"]["min_damage"].asInt(),
	       config["compoundBow"]["max_damage"].asInt()) {
        this->id = 17;
        this->name = "Arco Compuesto";
        this->ranged = true;
        this->magical = false;
    }
