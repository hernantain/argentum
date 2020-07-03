#ifndef _SERVER_NPC
#define _SERVER_NPC

#include <stdlib.h>
#include <time.h>
#include <jsoncpp/json/json.h>

#include "server_movement.h"
#include "server_character.h"

#include "../common_collision_info.h"

/* Clase que representa a un NPC del juego.  Es no copiable. */
class NPC {
protected:
    Json::Value& config;
    Movement movement;
    CollisionInfo &collisionInfo;
    int id;
    bool alive;
    int level, life, min_damage, max_damage, defense_points;

    // No copiable.
    NPC(const NPC&) = delete;
    NPC& operator=(const NPC&) = delete;

    int get_damage();
    int get_defense();
    int gold_drop();

public:
    // Contructor, recibe el id, la vida inicial
    NPC(Json::Value& config, CollisionInfo &collisionInfo);

    // Devuelve el id
    int get_id();

    // Devuelve el nivel
    int get_level();

    // Devuelve la vida
    int get_life();

    // Le quita vida al personaje
    void take_off_life(int life_points);

    // Dropea la recompensa si la hubiere del NPC
    void drop();

    // Ataca a un personaje del juego
    void attack(Character& other);

    // Defiende al NPC de un ataque
    // Devuelve el daño final que fue realizado
    int defense(int damage);

    // Mueve el NPC hacia la derecha
    void move_right(int velocity);

    // Mueve el NPC hacia la izquierda
    void move_left(int velocity);

    // Mueve el NPC hacia arriba
    void move_top(int velocity);

    // Mueve el NPC hacia abajo
    void move_down(int velocity);

    // Getter de la posicion del cuerpo en X
    int get_body_pos_X();

    // Getter de la posicion de la cabeza en X
    int get_body_pos_Y();
};


#endif //_NPC
