#ifndef _SERVER_PLATE_ARMOR
#define _SERVER_PLATE_ARMOR

#include "server_armor.h"

/* Clase que representa a una armadura de placas del juego */
class PlateArmor : public Armor {
public:
    // Contructor
    PlateArmor(Json::Value& config);
};


#endif //_SERVER_ARMOR
