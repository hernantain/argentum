#ifndef _SERVER_HAMMER
#define _SERVER_HAMMER

#include "server_weapon.h"

/* Clase que representa a una martillo del juego */
class Hammer : public Weapon {
public:
    // Contructor
    Hammer(Json::Value& config);
};


#endif //_SERVER_HAMMER
