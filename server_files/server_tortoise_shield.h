#ifndef _SERVER_TORTOISE_SHIELD
#define _SERVER_TORTOISE_SHIELD

#include "server_shield.h"

/* Clase que representa a un escudo de tortuga del juego */
class TortoiseShield : public Shield {
public:
    // Contructor
    explicit TortoiseShield(Json::Value& config);
};


#endif //_SERVER_TORTOISE_SHIELD
