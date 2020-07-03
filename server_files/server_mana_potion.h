#ifndef _SERVER_MANA_POTION
#define _SERVER_MANA_POTION

#include "server_potion.h"

/* Clase que representa a una pocion de mana del juego */
class ManaPotion : public Potion {
public:
    // Contructor
    ManaPotion(Json::Value &config);
};

#endif //_SERVER_MANA_POTION
