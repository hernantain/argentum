#ifndef _SERVER_ELFIC_FLUTE
#define _SERVER_ELFIC_FLUTE

#include "server_weapon.h"

/* Clase que representa a una flauta elfica del juego */
class ElficFlute : public Weapon {
public:
    // Contructor
    ElficFlute(Json::Value& config);
};


#endif //_SERVER_ELFIC_FLUTE
