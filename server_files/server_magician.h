#ifndef _SERVER_MAGICIAN
#define _SERVER_MAGICIAN

#include "server_character_class.h"

/* Clase que representa a la clase mago del juego */
class Magician : public CharacterClass {
public:
    // Contructor
    Magician(Json::Value& config);
};


#endif //_SERVER_MAGICIAN
