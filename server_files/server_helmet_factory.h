#ifndef _HELMET_FACTORY_H
#define _HELMET_FACTORY_H

#include "server_helmet.h"
#include "server_iron_helmet.h"
#include "server_hood.h"
#include "server_magic_hat.h"

/* Clase que funciona como factory para los distintos tipos de cascos de la aplicacion */
class HelmetFactory {
public:
    HelmetFactory() {}

    /* Recibiendo un id crea el casco correspondiente */
    Helmet make_helmet(const int helmet_id, Json::Value& config);

    ~HelmetFactory() {}
};

#endif // _HELMET_FACTORY_H
