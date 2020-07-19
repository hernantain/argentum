#ifndef _SERVER_ARMOR
#define _SERVER_ARMOR

#include "server_item.h"

/* Clase que representa a una armadura del juego */
class Armor : public Item {
private:
    int min_defense, max_defense;

public:
    // Contructor
    Armor(int min_defense, int max_defense);

    Armor() = default;

    // Devuelve la defensa de la armadura
    int get_defense() const;
};


#endif //_SERVER_ARMOR
