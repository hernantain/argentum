#ifndef _SERVER_NPC
#define _SERVER_NPC

#include <stdlib.h>
#include <time.h>
#include <jsoncpp/json/json.h>

#include "server_movement.h"
#include "server_character.h"
#include "server_attackable.h"

#include "../common_files/common_collision_info.h"

/* Clase que representa a un NPC del juego.  Es no copiable. */
class NPC : public Attackable {
protected:
    Json::Value& config;
    Movement movement;
    uint8_t id;
    bool alive;
    int16_t level, life, max_life;
    int min_damage, max_damage, defense_points;

    // No copiable.
    NPC(const NPC&) = delete;
    NPC& operator=(const NPC&) = delete;

    // bool can_attack(Character& other);
    bool can_attack(Attackable& other);
    int get_damage();
    int get_defense();
    int gold_drop();

public:
    // Contructor, recibe el id, la vida inicial
    NPC(Json::Value& config, CollisionInfo &collisionInfo);

    // Devuelve el id
    uint8_t get_id();

    // Devuelve el nivel
    int16_t get_level();

    // Devuelve la vida
    int16_t get_life();

    // Devuelve la vida maxima
    int16_t get_max_life();

    // Booleano devuelve verdadero si el NPC se encuentra en una zona segura
    bool is_safe();

    // Booleano devuelve verdadero si esta vivo el NPC
    bool is_alive();

    bool is_newbie();

    // Le quita vida al personaje
    void take_off_life(int life_points);

    // Dropea la recompensa si la hubiere del NPC
    void drop();

    // Ataca a un personaje del juego
    // void attack(Character& other);
    void attack(Attackable& other) override;

    // Defiende al NPC de un ataque
    // Devuelve el daño final que fue realizado
    int defense(int damage) override;

    // Booleano que devuelve si el NPC esta cerca de la posicion
    bool is_near(int posX, int posY);

    // Mueve el NPC hacia la derecha
    void move_right();

    // Mueve el NPC hacia la izquierda
    void move_left();

    // Mueve el NPC hacia arriba
    void move_top();

    // Mueve el NPC hacia abajo
    void move_down();

    // Mueve el NPC hacia una direccion random
    void move_random();

    // Devuelve la direccion hacia donde se mueve el NPC
    int get_body_facing();

    // Getter de la posicion del cuerpo en X
    int16_t get_body_pos_X() const;

    // Getter de la posicion de la cabeza en X
    int16_t get_body_pos_Y() const;
};


#endif //_NPC
