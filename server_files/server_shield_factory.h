#ifndef _SHIELD_FACTORY
#define _SHIELD_FACTORY

#include "server_shield.h"
#include "server_tortoise_shield.h"
#include "server_iron_shield.h"


/* Clase que funciona como factory para los distintos tipos de armas de la aplicacion */
class ShieldFactory {
public:
    ShieldFactory() {}

    /* Recibiendo un id crea el arma correspondiente */
    Shield make_shield(const int shield_id, Json::Value& config);

    ~ShieldFactory() {}
};



#endif
