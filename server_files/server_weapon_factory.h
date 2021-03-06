#ifndef _WEAPON_FACTORY_H
#define _WEAPON_FACTORY_H

#include "server_weapon.h"
#include "server_axe.h"
#include "server_hammer.h"
#include "server_sword.h"
#include "server_ash_staff.h"
#include "server_gnarled_staff.h"
#include "server_crimp_staff.h"
#include "server_simple_bow.h"
#include "server_compound_bow.h"
#include "server_default_weapon.h"

/* Clase que funciona como factory para los distintos tipos de armas de la aplicacion */
class WeaponFactory {
public:

    /* Recibiendo un id crea el arma correspondiente */
    static Weapon make_weapon(const uint8_t weapon_id, Json::Value& config);

};

#endif // WeaponFactory
