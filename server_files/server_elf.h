#ifndef _SERVER_ELF
#define _SERVER_ELF

#include "server_race.h"

/* Clase que representa a la raza elfo del juego */
class Elf : public Race {
public:
    // Contructor
    Elf(Json::Value& config);
};


#endif //_SERVER_ELF
