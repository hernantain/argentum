#ifndef _SERVER_LIFE_POINTS
#define _SERVER_LIFE_POINTS

#include <stdint.h>

/* Clase que representa a los ptos de vida de un personaje */
class LifePoints {
private:
    int constitution;
    float class_multiplier, race_multiplier;
    int16_t current_life, max_life;

public:
    // Contructor, recibe la constitucion del personaje
    LifePoints(int constitution, float class_multiplier, float race_multiplier);

    // Disminuye la vida en life_points
    void subtract(int life_points);

    // Aumenta la vida en life_points
    void add(int life_points);

    // Devuelve la vida actual
    int16_t current() const;

    // Devuelve el maximo de vida
    int16_t max() const;

    // Setter de la max vida para el nivel recibido
    void set_new_max(int level);
};


#endif //_SERVER_LIFE_POINTS
