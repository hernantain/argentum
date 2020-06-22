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
    Shield shield;
    Helmet helmet;
    Armor armor;

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

    // Obtiene el daño del arma equipada si la hubiere
    int get_weapon_damage();

    // Obtiene el consumo de mana del arma si lo hubiere
    int get_weapon_consumption();

    // Devuelve verdadero si el arma equipada es magica, falso i no
    bool is_weapon_magical();

    // Obtiene el daño del arma equipada si la hubiere
    int get_equipment_defense();
};


#endif //_SERVER_ITEM
