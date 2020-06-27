#ifndef _SERVER_MOVEMENT
#define _SERVER_MOVEMENT

// Which was the last movement.
enum _lastMovement {
    LEFT,
    RIGHT,
    TOP,
    DOWN
};

/* Clase encargada de la movilidad de un personaje. */
class Movement {
private:
    int bodyPosX, bodyPosY;
    int headPosX, headPosY;
    _lastMovement last_movement;
  
    // No copiable
    Movement(const Movement&) = delete;
    Movement& operator=(const Movement&) = delete;

public:
    // Constructor.
    explicit Movement();

    // Devuelve un float indicando la posición horizontal del personaje.
    int get_horizontal_position();

    // Devuelve un float indicando la posición vertical del personaje.
    int get_vertical_position();

    // Devuelve un float indicando la velocidad horizontal del personaje.
    int get_horizontal_velocity();

    // Devuelve un float indicando la velocidad vertical del personaje.
    int get_vertical_velocity();

    // Setea el movimiento del personaje hacia la derecha
    void move_right(int velocity);

    // Setea el movimiento del personaje hacia la izquierda
    void move_left(int velocity);

    // Setea el movimiento del personaje hacia la derecha
    void move_top(int velocity);

    // Setea el movimiento del personaje hacia la izquierda
    void move_down(int velocity);

    // Devuelve true si el personaje está mirando hacia la derecha, false en caso contrario.
    bool is_facing_right();

    // Devuelve true si el personaje está mirando hacia la izquierda, false en caso contrario.
    bool is_facing_left();

    // Devuelve true si el personaje está mirando hacia arriba, false en caso contrario.
    bool is_facing_top();

    // Devuelve true si el personaje está mirando hacia abajo, false en caso contrario.
    bool is_facing_down();

    // Devuelve un booleano indicando si puede moverse o no.
    // TODO: aca deberia recibir una referencia al mapa o algo asi.
    bool can_move();

    // Devuelve un booleano indicando si está colisionando
    // con algún objeto.
    bool is_colliding();

};


#endif //_SERVER_MOVEMENT
