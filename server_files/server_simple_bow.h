#ifndef _SERVER_SIMPLE_BOW
#define _SERVER_SIMPLE_BOW

#include "server_weapon.h"

/* Clase que representa a un Arco simple del juego */
class SimpleBow : public Weapon {
public:
    // Contructor
    SimpleBow(Json::Value& config);
};


#endif //_SERVER_SIMPLE_BOW
