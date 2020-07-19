#ifndef _SERVER_MANA_POINTS
#define _SERVER_MANA_POINTS

#include <stdint.h>

/* Clase que representa a los puntos de mana de un personaje */
class ManaPoints {
private:
    int intelligence;
    float class_multiplier, race_multiplier;
    int16_t current_mana, max_mana;

public:
    // Contructor, recibe la inteligencia de la raza
    ManaPoints(int intelligence, float class_multiplier, float race_multiplier);

    // Disminuye la mana en mana_points
    void subtract(const int mana_points);

    // Aumenta la mana en mana_points
    void add(const int mana_points);

    // Booleano devuelve verdadero si la mana se encuentra llena
    bool is_full() const;
    
    // Devuelve la mana actual
    int16_t current() const;

    // Devuelve la mana maxima
    int16_t max() const;

    // Setter de la max mana para el nivel recibido
    void set_new_max(const int level);
};


#endif //_SERVER_MANA_POINTS
