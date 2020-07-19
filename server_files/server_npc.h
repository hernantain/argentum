#ifndef _SERVER_NPC
#define _SERVER_NPC

#include <stdlib.h>
#include <time.h>
#include <jsoncpp/json/json.h>

#include "server_movement.h"
#include "server_character.h"
#include "server_attackable.h"
#include "server_item_factory.h"

#include "../common_files/common_collision_info.h"

/* Clase que representa a un NPC del juego.  Es no copiable. */
class NPC : public Attackable {
protected:
    Json::Value& config;
    Movement movement;
    uint16_t id;
    bool alive;
    int16_t level, life, max_life;
    int min_damage, max_damage, defense_points;
    int width, height;

    // No copiable.
    NPC(const NPC&) = delete;
    NPC& operator=(const NPC&) = delete;

    bool can_attack(const Attackable& other) const;
    int get_damage() const;
    int get_defense() const;
    int gold_drop() const;
    void drop_gold(Item &drop_item, int gold) const;
    void drop_potion(Item &drop_item) const;
    void drop_random_item(Item &drop_item) const;

public:
    // Contructor, recibe el id, la vida inicial
    NPC(Json::Value& config, CollisionInfo &collisionInfo);

    // Devuelve el id
    uint16_t get_id() const;

    // Devuelve el nivel
    int16_t get_level() const;

    // Devuelve la vida
    int16_t get_life() const;

    // Devuelve la vida maxima
    int16_t get_max_life() const;

    // Devuelve el ancho del NPC
    int get_width() const;

    // Devuelve el alto del NPC
    int get_height() const;

    // Booleano devuelve verdadero si el NPC se encuentra en una zona segura
    bool is_safe() const;

    // Chequea que tanto vos como el otro jugador esten en zona segura
    bool attack_zone(const Attackable& other) const;

    // Booleano devuelve verdadero si esta vivo el NPC
    bool is_alive() const;

    bool is_newbie() const;

    // Le quita vida al personaje
    void take_off_life(const int life_points);

    // Dropea la recompensa si la hubiere del NPC
    void drop();

    // Dropea la recompensa si la hubiere del NPC
    void drop_items(std::vector<Item> &worldItems);

    // Ataca a un personaje del juego
    // void attack(Character& other);
    void attack(Attackable& other) override;

    // Defiende al NPC de un ataque
    // Devuelve el daño final que fue realizado
    int defense(const int damage) override;

    // Booleano que devuelve si el NPC esta cerca de la posicion
    bool is_near(const int posX, const int posY) const;

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

    // Acerca al NPC hacia la direccion posX, posY
    void move_to(const Attackable& other);

    // Devuelve la direccion hacia donde se mueve el NPC
    int get_body_facing() const;

    // Getter de la posicion del cuerpo en X
    int16_t get_body_pos_X() const;

    // Getter de la posicion de la cabeza en X
    int16_t get_body_pos_Y() const;

    virtual ~NPC();
};


#endif //_NPC
