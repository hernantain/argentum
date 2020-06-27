#include "server_hood.h"

Hood::Hood(Json::Value &config) : 
    Helmet(config["hoodHelmet"]["min_defense"].asInt(),
	       config["hoodHelmet"]["max_defense"].asInt()) {
        this->id = 4;
        this->name = "Capucha";
    }
