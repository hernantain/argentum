#include "server_iron_helmet.h"

IronHelmet::IronHelmet(Json::Value &config) : 
    Helmet(config["ironHelmet"]["min_defense"].asInt(),
	       config["ironHelmet"]["max_defense"].asInt()) {
        this->id = 5;
        this->name = "Casco de Hierro";
    }
