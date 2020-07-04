#ifndef _SERVER_CRIMP_STAFF
#define _SERVER_CRIMP_STAFF

#include "server_weapon.h"

/* Clase que representa a un baculo Engarzado del juego */
class CrimpStaff : public Weapon {
public:
    // Contructor
    CrimpStaff(Json::Value& config);
};


#endif //_SERVER_CRIMP_STAFF
