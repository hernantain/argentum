#ifndef _SERVER_LIFE_POTION
#define _SERVER_LIFE_POTION

#include "server_potion.h"

/* Clase que representa a una pocion de vida del juego */
class LifePotion : public Potion {
public:
    // Contructor
    LifePotion(Json::Value &config);
};


#endif //_SERVER_LIFE_POTION
