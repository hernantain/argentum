#ifndef _SERVER_EQUIPMENT
#define _SERVER_EQUIPMENT

#include "server_weapon.h"
#include "server_armor.h"
#include "server_shield.h"
#include "server_helmet.h"
#include "server_item.h"
#include "server_default_armor.h"
#include "server_default_shield.h"
#include "server_default_helmet.h"
#include "server_default_weapon.h"

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

    // Initializer of equipment
    void initialize_equipment();

    // Equipa un arma al personaje
    void equip_weapon(Weapon& item);

    // Equipa una armadura al personaje
    void equip_armor(Armor& item);

    // Equipa un escudo al personaje
    void equip_shield(Shield& item);

    // Equipa un casco al personaje
    void equip_helmet(Helmet& item);

    // Obtiene el daño del arma equipada si la hubiere
    int get_weapon_damage() const;

    // Obtiene el consumo de mana del arma si lo hubiere
    int get_weapon_consumption() const;

    // Devuelve verdadero si el arma equipada es magica, falso si no
    bool is_weapon_magical() const;

    // Devuelve verdadero si el arma equipada es de rango, falso si no
    bool is_weapon_ranged() const;

    // Devuelve el arma actual equipada, -1 si es la default
    int16_t current_weapon() const;

    // Devuelve el escudo actual equipada, -1 si es la default
    int16_t current_shield() const;

    // Devuelve la armadura actual equipada, -1 si es la default
    int16_t current_armor() const;

    // Devuelve el casco actual equipada, -1 si es la default
    int16_t current_helmet() const;

    // Obtiene el daño del arma equipada si la hubiere
    int get_equipment_defense() const;
};


#endif //_SERVER_ITEM
