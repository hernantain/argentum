#include "server_tortoise_shield.h"

TortoiseShield::TortoiseShield(Json::Value &config) : 
    Shield(config["tortoiseShield"]["min_defense"].asInt(),
	       config["tortoiseShield"]["max_defense"].asInt()) {
        this->id = 7;
        this->name = "Escudo de Tortuga";
    }
