#ifndef _ARMOR_FACTORY_H
#define _ARMOR_FACTORY_H

#include "server_armor.h"
#include "server_blue_robe.h"
#include "server_leather_armor.h"
#include "server_plate_armor.h"

/* Clase que funciona como factory para los distintos tipos de armaduras de la aplicacion */
class ArmorFactory {
public:

    /* Recibiendo un id crea el casco correspondiente */
    static Armor make_armor(const int armor_id, Json::Value& config);
};

#endif // _ARMOR_FACTORY_H
