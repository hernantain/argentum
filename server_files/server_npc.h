#ifndef _SERVER_NPC
#define _SERVER_NPC

#include <stdlib.h>
#include <time.h>
#include <jsoncpp/json/json.h>
#include "server_movement.h"

/* Clase que representa a un NPC del juego.  Es no copiable. */
class NPC {
private:
    size_t id;
    Json::Value& config;
    Movement movement;
    bool alive;
    int level;
    int life;

    // No copiable.
    NPC(const NPC&) = delete;
    NPC& operator=(const NPC&) = delete;

public:
    // Contructor, recibe el id, la vida inicial
    NPC(size_t id, Json::Value& config);

    // Devuelve el id
    int get_id();

    // Devuelve el nivel
    int get_level();

    // Devuelve la vida
    int get_life();

    // Dropea la recompensa si la hubiere del NPC
    void drop();

    // Ataca a otro personaje o a un NPC
    // void attack(Character& other);

    // Defiende al NPC de un ataque
    void defense(int damage);

    // Mueve al NPC
    void move(int velocity);

    // Getter de la posicion del cuerpo en X
    int get_body_pos_X();

    // Getter de la posicion de la cabeza en X
    int get_body_pos_Y();
};


#endif //_NPC
