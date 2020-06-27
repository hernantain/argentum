#ifndef _SERVER_MAGIC_HAT
#define _SERVER_MAGIC_HAT

#include "server_helmet.h"

/* Clase que representa a un sombrero magico del juego */
class MagicHat : public Helmet {
public:
    // Contructor
    MagicHat(Json::Value& config);
};


#endif //_SERVER_MAGIC_HAT
