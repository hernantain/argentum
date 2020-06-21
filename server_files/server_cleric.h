#ifndef _SERVER_CLERIC
#define _SERVER_CLERIC

#include "server_character_class.h"

/* Clase que representa a la clase clerigo del juego */
class Cleric : public CharacterClass {
public:
    // Contructor
    Cleric(Json::Value& config);
};


#endif //_SERVER_CLERIC
