#include "server_dwarf.h"

#define DWARF_ID 3

Dwarf::Dwarf(Json::Value &config) : 
    Race(config["initialAttributes"].asInt()) {
        this->id = DWARF_ID;
        this->strength += config["dwarf"]["strength_modifier"].asInt();
        this->intelligence -= config["dwarf"]["intelligence_modifier"].asInt();
        this->constitution += config["dwarf"]["constitution_modifier"].asInt();
        
        this->life_multiplier = config["dwarf"]["life_multiplier"].asFloat();
        this->mana_multiplier = config["dwarf"]["mana_multiplier"].asFloat();
        this->recovery_multiplier = config["dwarf"]["recovery_multiplier"].asFloat();
    }
