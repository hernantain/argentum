#ifndef _SERVER_ASH_STAFF
#define _SERVER_ASH_STAFF

#include "server_weapon.h"

/* Clase que representa a un baculo de fresno del juego */
class AshStaff : public Weapon {
public:
    // Contructor
    AshStaff(Json::Value& config);
};


#endif //_SERVER_ASH_STAFF
