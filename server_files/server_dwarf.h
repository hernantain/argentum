#ifndef _SERVER_DWARF
#define _SERVER_DWARF

#include "server_race.h"

/* Clase que representa a la raza enano del juego */
class Dwarf : public Race {
public:
    // Contructor
    Dwarf(Json::Value& config);
};


#endif //_SERVER_DWARF
