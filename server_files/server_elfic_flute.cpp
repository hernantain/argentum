#include "server_elfic_flute.h"

ElficFlute::ElficFlute(Json::Value &config) : 
    Weapon(config["elficFlute"]["min_damage"].asInt(),
	       config["elficFlute"]["max_damage"].asInt()) {
        this->id = 12;
        this->name = "Flauta Elfica";
        this->ranged = true;
        this->magical = true;
        this->mana_consumption = config["elficFlute"]["mana"].asInt();
    }
