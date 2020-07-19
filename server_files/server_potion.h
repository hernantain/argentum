#ifndef _SERVER_POTION
#define _SERVER_POTION

#include "server_item.h"

/* Clase que representa a una pocion del juego */
class Potion : public Item {
protected:
    int recovery_points;
public:
    // Contructor
    Potion(int recovery_points);

    int get_recovery_points() const;
};

#endif //_SERVER_POTION
