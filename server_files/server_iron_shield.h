#ifndef _SERVER_IRON_SHIELD
#define _SERVER_IRON_SHIELD

#include "server_shield.h"

/* Clase que representa a un escudo de hierro del juego */
class IronShield : public Shield {
public:
    // Contructor
    IronShield(Json::Value& config);
};


#endif //_SERVER_IRON_SHIELD
