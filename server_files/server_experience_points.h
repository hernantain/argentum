#ifndef _SERVER_EXPERIENCE_POINTS
#define _SERVER_EXPERIENCE_POINTS

#include <stdint.h>

/* Clase que representa a los puntos de experiencia de un personaje */
class ExperiencePoints {
private:
    int difficulty_constant;
    float level_multiplier;
    int16_t current_exp;
    int16_t max_exp;

public:
    // Contructor
    ExperiencePoints(int difficulty_constant, float level_multiplier);

    // Disminuye la experiencia en points
    void subtract(int points);

    // Aumenta la experiencia en _points
    void add(int points);
    
    // Devuelve la experiencia actual
    int16_t current() const;

    // Devuelve la maxima del nivel
    int16_t max() const;

    // Setter de la max experiencia para el nivel recibido
    void set_new_max(int level);
};


#endif //_SERVER_EXPERIENCE_POINTS
