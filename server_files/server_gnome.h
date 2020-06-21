#ifndef _SERVER_GNOME
#define _SERVER_GNOME

#include "server_race.h"

/* Clase que representa a la raza gnomo del juego */
class Gnome : public Race {
public:
    // Contructor
    Gnome(Json::Value& config);
};


#endif //_SERVER_GNOME
