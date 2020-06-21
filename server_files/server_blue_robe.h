#ifndef _SERVER_BLUE_ROBE
#define _SERVER_BLUE_ROBE

#include "server_armor.h"

/* Clase que representa a una tunica azul del juego */
class BlueRobe : public Armor {
public:
    // Contructor
    BlueRobe(Json::Value& config);
};


#endif //_SERVER_ARMOR
