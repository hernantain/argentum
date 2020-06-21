#include "server_leather_armor.h"

LeatherArmor::LeatherArmor(Json::Value &config) : 
    Armor(config["leatherArmor"]["min_defense"].asInt(),
	      config["leatherArmor"]["max_defense"].asInt()) {
        this->id = 1;
        this->name = "Armadura de Cuero";
    }
