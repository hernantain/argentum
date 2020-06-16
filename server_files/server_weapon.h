#ifndef _SERVER_WEAPON
#define _SERVER_WEAPON

#include "server_item.h"

/* Clase que representa a un arma del juego */
class Weapon : public Item {
private:
    int min_damage;
    int max_damage;

public:
    // Contructor
    Weapon(int min_damage, int max_damage);

    // Default C
    Weapon() = default;

    // Devuelve el ataque del arma
    int get_damage();

};


#endif //_SERVER_WEAPON
