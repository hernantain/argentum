#ifndef _SERVER_LEATHER_ARMOR
#define _SERVER_LEATHER_ARMOR

#include "server_armor.h"

/* Clase que representa a una armadura del juego */
class LeatherArmor : public Armor {
public:
    // Contructor
    LeatherArmor(Json::Value& config);
};


#endif //_SERVER_ARMOR
