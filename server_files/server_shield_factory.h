#ifndef _SHIELD_FACTORY
#define _SHIELD_FACTORY

#include "server_shield.h"
#include "server_tortoise_shield.h"
#include "server_iron_shield.h"


/* Clase que funciona como factory para los distintos tipos de armas de la aplicacion */
class ShieldFactory {
public:

    /* Recibiendo un id crea el arma correspondiente */
    static Shield make_shield(const uint8_t shield_id, Json::Value& config);
};



#endif
