#ifndef _SERVER_EQUIPMENT
#define _SERVER_EQUIPMENT

#include "server_weapon.h"
#include "server_armor.h"
#include "server_shield.h"
#include "server_helmet.h"
#include "server_item.h"

/* Clase que representa a un item del juego */
class Equipment {
private:
    Weapon weapon;
    Armor armor;
    Shield shield;
    Helmet helmet;

public:
    // Contructor
    Equipment();

    // Equipa un arma al personaje
    void equip_weapon(Weapon& item);

    // Equipa una armadura al personaje
    void equip_armor(Armor& item);

    // Equipa un escudo al personaje
    void equip_shield(Shield& item);

    // Equipa un casco al personaje
    void equip_helmet(Helmet& item);

};


#endif //_SERVER_ITEM
