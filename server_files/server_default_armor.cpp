#include "server_default_armor.h"

#define NO_DEFENSE 0
#define DEFAULT_ID 0

DefaultArmor::DefaultArmor() : 
    Armor(NO_DEFENSE, NO_DEFENSE) {
        this->id = DEFAULT_ID;
        this->name = "Ropa Comun";
    }
