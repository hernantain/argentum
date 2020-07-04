#ifndef _SERVER_GNARLED_STAFF
#define _SERVER_GNARLED_STAFF

#include "server_weapon.h"

/* Clase que representa a un baculo nudoso del juego */
class GnarledStaff : public Weapon {
public:
    // Contructor
    GnarledStaff(Json::Value& config);
};


#endif //_SERVER_GNARLED_STAFF
