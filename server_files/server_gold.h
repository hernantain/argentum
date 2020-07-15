#ifndef _SERVER_GOLD
#define _SERVER_GOLD

#include "server_item.h"

/* Clase que representa al oro de un personaje en el juego */
class Gold : public Item {
public:
    // Contructor
    Gold(int initial_amount);

    // Getter de la cantidad de oro
    int get_gold() const;
};


#endif //_SERVER_GOLD
