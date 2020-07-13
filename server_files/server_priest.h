#ifndef _SERVER_PRIEST
#define _SERVER_PRIEST

#include "server_citizen.h"

/* Clase que representa a un Sacerdote del juego.  Es no copiable. */
class Priest : public Citizen {
public:
    // Contructor
    using Citizen::Citizen;
};

#endif //_SERVER_PRIEST
