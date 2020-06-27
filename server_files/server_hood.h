#ifndef _SERVER_HOOD
#define _SERVER_HOOD

#include "server_helmet.h"

/* Clase que representa a una capucha del juego */
class Hood : public Helmet {
public:
    // Contructor
    explicit Hood(Json::Value& config);
};


#endif //_SERVER_HOOD
