#ifndef _SERVER_LIFE_POINTS
#define _SERVER_LIFE_POINTS

/* Clase que representa a los ptos de vida de un personaje */
class LifePoints {
private:
    int current_life;
    int max_life;

    int initial_life(int constitution, float class_multiplier, float race_multiplier);
public:
    // Contructor, recibe la constitucion del personaje
    LifePoints(int constitution, float class_multiplier, float race_multiplier);

    // Disminuye la vida en life_points
    void subtract(int life_points);

    // Aumenta la vida en life_points
    void add(int life_points);

    // Devuelve la vida actual
    int current();

    // Devuelve el maximo de vida
    int max();
};


#endif //_SERVER_LIFE_POINTS
