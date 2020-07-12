#ifndef _SERVER_BANKER
#define _SERVER_BANKER

/* Clase que representa a un Banquero del juego.  Es no copiable. */
class Banker {
private:
    int16_t posX, posY;

public:
    // Contructor
    Banker(int16_t posX, int16_t posY);

    // Getter de la posicion del cuerpo en X
    int16_t get_pos_X() const;

    // Getter de la posicion de la cabeza en X
    int16_t get_pos_Y() const;
};

#endif //_SERVER_BANKER
