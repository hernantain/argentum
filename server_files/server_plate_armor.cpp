#include "server_plate_armor.h"

PlateArmor::PlateArmor(Json::Value &config) : 
    Armor(config["plateArmor"]["min_defense"].asInt(),
	      config["plateArmor"]["max_defense"].asInt()) {
        this->id = 2;
        this->name = "Armadura de Placas";
    }
