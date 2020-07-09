#ifndef _SERVER_MOVEMENT
#define _SERVER_MOVEMENT

#include "../common_files/common_collision_info.h"

// Which was the last movement.
enum _lastMovement {
    STAND,
    LEFT,
    RIGHT,
    TOP,
    DOWN
};

/* Clase encargada de la movilidad de un personaje. */
class Movement {
private:
    CollisionInfo &collisionInfo;
    int bodyPosX, bodyPosY;
    // int headPosX, headPosY;
    _lastMovement last_movement;
  
    // No copiable
    Movement(const Movement&) = delete;
    Movement& operator=(const Movement&) = delete;

public:
    // Constructor.
    // explicit Movement();

    Movement(CollisionInfo &collisionInfo);

    // Devuelve un int indicando la posicion en X del cuerpo.
    int get_horizontal_body_position() const;

    // Devuelve un int indicando la posicion en Y del cuerpo.
    int get_vertical_body_position() const;

    // Setea el movimiento del personaje hacia la derecha
    void move_right(int velocity, CollisionInfo &collisionInfo);

    // Setea el movimiento del personaje hacia la izquierda
    void move_left(int velocity, CollisionInfo &collisionInfo);

    // Setea el movimiento del personaje hacia la derecha
    void move_top(int velocity, CollisionInfo &collisionInfo);

    // Setea el movimiento del personaje hacia la izquierda
    void move_down(int velocity, CollisionInfo &collisionInfo);

    // Setea el movimiento del personaje hacia una direccion random
    void move_random(int velocity, CollisionInfo &collisionInfo);

    // Detiene el movimiento.
    void stop_moving();

    _lastMovement get_facing_direction();
  
    // Booleano que devuelve verdadero si posX y posY estan cerca del personaje
    bool is_near(int posX, int posY);

    // Booleano que devuelve verdadero si posX esta cerca del personaje bodyPosX
    bool is_near_X(int posX);

    // Booleano que devuelve verdadero si posY esta cerca del personaje bodyPosY
    bool is_near_Y(int posY);


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
    // bool can_move(int velocityX=0, int velocityY=0);

    // Devuelve un booleano indicando si está colisionando
    // con algún objeto.
    bool is_colliding();

    // Corrige la posicion en X si el personaje se va de los limites del mapa
    void check_out_of_bounds_X(int velocity);

    // Corrige la posicion en Y si el personaje se va de los limites del mapa
    void check_out_of_bounds_Y(int velocity);

    bool check_map_collision(CollisionInfo &collisionInfo);

};


#endif //_SERVER_MOVEMENT
