#ifndef _SERVER_LIFE_POINTS
#define _SERVER_LIFE_POINTS

/* Clase que representa a los ptos de vida de un personaje */
class LifePoints {
private:
    int current_life;
    int max_life;

public:
    // Contructor, recibe la vida inicial
    LifePoints(int life);

    // Disminuye la vida en life_points
    void subtract(int life_points);

    // Aumenta la vida en life_points
    void add(int life_points);

    // Devuelve la vida actual
    int current();
};


#endif //_SERVER_LIFE_POINTS
