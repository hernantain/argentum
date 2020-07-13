#ifndef _SERVER_BANKER
#define _SERVER_BANKER

#include "server_citizen.h"

/* Clase que representa a un Banquero del juego.  Es no copiable. */
class Banker : public Citizen {
public:
    // Contructor
    using Citizen::Citizen;
};

#endif //_SERVER_BANKER
