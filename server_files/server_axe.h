#ifndef _SERVER_AXE
#define _SERVER_AXE

#include "server_weapon.h"

/* Clase que representa a una hacha del juego */
class Axe : public Weapon {
public:
    // Contructor
    Axe(Json::Value& config);
};


#endif //_SERVER_AXE
