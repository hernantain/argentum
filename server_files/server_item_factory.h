#ifndef _ITEM_FACTORY_H
#define _ITEM_FACTORY_H

#include "server_item.h"
#include "server_blue_robe.h"
#include "server_leather_armor.h"
#include "server_plate_armor.h"
#include "server_iron_helmet.h"
#include "server_hood.h"
#include "server_magic_hat.h"
#include "server_tortoise_shield.h"
#include "server_iron_shield.h"
#include "server_axe.h"
#include "server_hammer.h"
#include "server_elfic_flute.h"
#include "server_sword.h"
#include "server_ash_staff.h"
#include "server_gnarled_staff.h"
#include "server_crimp_staff.h"
#include "server_simple_bow.h"
#include "server_compound_bow.h"
#include "server_life_potion.h"
#include "server_mana_potion.h"

/* Clase que funciona como factory para los distintos tipos de Items de la aplicacion */
class ItemFactory {
public:

    /* Recibiendo un id crea el item correspondiente */
    static Item make_item(const int16_t item_id, Json::Value& config);
};

#endif // _ITEM_FACTORY_H
