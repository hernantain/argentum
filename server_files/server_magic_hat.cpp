#include "server_magic_hat.h"

MagicHat::MagicHat(Json::Value &config) : 
    Helmet(config["magicHat"]["min_defense"].asInt(),
	       config["magicHat"]["max_defense"].asInt()) {
        this->id = 6;
        this->name = "Sombrero Magico";
    }
