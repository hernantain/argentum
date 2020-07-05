#ifndef _SERVER_SHIELD
#define _SERVER_SHIELD

#include "server_item.h"

/* Clase que representa a un escudo del juego */
class Shield : public Item {
private:
    int min_defense, max_defense;

public:
    // Contructor
    Shield(int min_defense, int max_defense);

    Shield() = default;

    // Devuelve la defensa del escudo
    int get_defense();
};


#endif //_SERVER_SHIELD
