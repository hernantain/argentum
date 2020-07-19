#ifndef _SERVER_WEAPON
#define _SERVER_WEAPON

#include "server_item.h"

/* Clase que representa a un arma del juego */
class Weapon : public Item {
protected:
    int min_damage, max_damage, mana_consumption;
    bool ranged, magical;

public:
    // Contructor
    Weapon(int min_damage, int max_damage);

    // Default C
    Weapon() = default;

    // Devuelve el ataque del arma
    int get_damage() const;

    // Devuelve verdadero si el arma ataca a distancia, falso si no
    int is_ranged() const;

    // Devuelve verdadero si el arma es magica, falso si no
    int is_magical() const;

    // Devuelve el consumo de mana del arma en cuestion
    int get_mana_consumption() const;

};


#endif //_SERVER_WEAPON
