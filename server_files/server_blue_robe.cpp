#include "server_blue_robe.h"

BlueRobe::BlueRobe(Json::Value &config) : 
    Armor(config["blueRobe"]["min_defense"].asInt(),
	      config["blueRobe"]["max_defense"].asInt()) {
        this->id = 3;
        this->name = "Tunica Azul";
    }
