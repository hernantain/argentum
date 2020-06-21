#include "server_iron_shield.h"

IronShield::IronShield(Json::Value &config) : 
    Shield(config["ironShield"]["min_defense"].asInt(),
	       config["ironShield"]["max_defense"].asInt()) {
        this->id = 8;
        this->name = "Escudo de Hierro";
    }
