#include "server_default_weapon.h"

#define NO_ATTACK 0
#define DEFAULT_ID 0

DefaultWeapon::DefaultWeapon() : 
    Weapon(NO_ATTACK, NO_ATTACK) {
        this->id = DEFAULT_ID;
        this->name = "Default Weapon";
        this->ranged = false;
        this->magical = false;
    }
