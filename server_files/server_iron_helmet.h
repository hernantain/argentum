#ifndef _SERVER_IRON_HELMET
#define _SERVER_IRON_HELMET

#include "server_helmet.h"

/* Clase que representa a un casco de hierro del juego */
class IronHelmet : public Helmet {
public:
    // Contructor
    IronHelmet(Json::Value& config);
};


#endif //_SERVER_IRON_HELMET
