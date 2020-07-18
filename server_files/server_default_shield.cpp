#include "server_default_shield.h"

#define NO_DEFENSE 0
#define DEFAULT_ID 0

DefaultShield::DefaultShield() : 
    Shield(NO_DEFENSE, NO_DEFENSE) {
        this->id = DEFAULT_ID;
        this->name = "Escudo default";
    }
