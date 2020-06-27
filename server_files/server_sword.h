#ifndef _SERVER_SWORD
#define _SERVER_SWORD

#include "server_weapon.h"

/* Clase que representa a una espada del juego */
class Sword : public Weapon {
public:
    // Contructor
    Sword(Json::Value& config);
};


#endif //_SERVER_SWORD
