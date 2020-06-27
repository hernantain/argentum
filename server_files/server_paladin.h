#ifndef _SERVER_PALADIN
#define _SERVER_PALADIN

#include "server_character_class.h"

/* Clase que representa a la clase paladin del juego */
class Paladin : public CharacterClass {
public:
    // Contructor
    Paladin(Json::Value& config);
};


#endif //_SERVER_PALADIN
