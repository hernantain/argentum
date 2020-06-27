#ifndef _SERVER_WARRIOR
#define _SERVER_WARRIOR

#include "server_character_class.h"

/* Clase que representa a la clase guerrero del juego */
class Warrior : public CharacterClass {
public:
    // Contructor
    explicit Warrior(Json::Value& config);
};


#endif //_SERVER_WARRIOR
