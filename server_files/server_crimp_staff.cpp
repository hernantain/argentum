#include "server_crimp_staff.h"

CrimpStaff::CrimpStaff(Json::Value &config) : 
    Weapon(config["crimpStaff"]["min_damage"].asInt(),
	       config["crimpStaff"]["max_damage"].asInt()) {
        this->id = 15;
        this->name = "Báculo Engarzado";
        this->ranged = true;
        this->magical = true;
        this->mana_consumption = config["gnarledStaff"]["mana"].asInt();
    }
