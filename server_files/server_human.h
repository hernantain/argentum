#ifndef _SERVER_HUMAN
#define _SERVER_HUMAN

#include "server_race.h"

/* Clase que representa a una capucha del juego */
class Human : public Race {
public:
    // Contructor
    Human(Json::Value& config);
};


#endif //_SERVER_HUMAN
