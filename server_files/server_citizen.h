#ifndef _SERVER_CITIZEN
#define _SERVER_CITIZEN

#include <iostream>

/* Clase que representa a un personaje Ciudadano del juego. Es no copiable. */
class Citizen {
private:
    int16_t posX, posY;

public:
    // Contructor
    Citizen(int16_t posX, int16_t posY);

    // Getter de la posicion del cuerpo en X
    int16_t get_pos_X() const;

    // Getter de la posicion de la cabeza en X
    int16_t get_pos_Y() const;
};

#endif //_SERVER_CITIZEN
