#include "server_gnarled_staff.h"

GnarledStaff::GnarledStaff(Json::Value &config) : 
    Weapon(config["gnarledStaff"]["min_damage"].asInt(),
	       config["gnarledStaff"]["max_damage"].asInt()) {
        this->id = 14;
        this->name = "Báculo Nudoso";
        this->ranged = true;
        this->magical = true;
    }
