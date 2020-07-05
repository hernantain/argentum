#ifndef _SERVER_HELMET
#define _SERVER_HELMET

#include "server_item.h"

/* Clase que representa a un casco del juego */
class Helmet : public Item {
private:
    int min_defense, max_defense;

public:
    // Contructor
    Helmet(int min_defense, int max_defense);

    Helmet() = default;

    // Devuelve la defensa del casco
    int get_defense();
};


#endif //_SERVER_HELMET
