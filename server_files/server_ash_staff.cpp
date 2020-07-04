#include "server_ash_staff.h"
#include <iostream>

AshStaff::AshStaff(Json::Value &config) : 
    Weapon(config["ashStaff"]["min_damage"].asInt(),
	       config["ashStaff"]["max_damage"].asInt()) {
        this->id = 13;
        this->name = "Báculo de Fresno";
        this->ranged = true;
        this->magical = true;
        this->mana_consumption = config["ashStaff"]["mana"].asInt();
    }
