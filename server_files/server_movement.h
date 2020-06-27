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

    // Devuelve un int indicando la posicion en X del cuerpo.
    int get_horizontal_body_position();

    // Devuelve un int indicando la posicion en X de la cabeza.
    int get_horizontal_head_position();

    // Devuelve un int indicando la posicion en Y del cuerpo.
    int get_vertical_body_position();

    // Devuelve un int indicando la posicion en Y de la cabeza
    int get_vertical_head_position();

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

    // Corrige la posicion en X si el personaje se va de los limites del mapa
    void check_out_of_bounds_X(int velocity);

    // Corrige la posicion en Y si el personaje se va de los limites del mapa
    void check_out_of_bounds_Y(int velocity);

};


#endif //_SERVER_MOVEMENT
