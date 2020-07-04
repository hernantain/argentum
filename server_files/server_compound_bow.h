#ifndef _SERVER_COMPOUND_BOW
#define _SERVER_COMPOUND_BOW

#include "server_weapon.h"

/* Clase que representa a un Arco compuesto del juego */
class CompoundBow : public Weapon {
public:
    // Contructor
    CompoundBow(Json::Value& config);
};


#endif //_SERVER_COMPOUND_BOW
