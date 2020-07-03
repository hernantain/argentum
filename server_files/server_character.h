#ifndef _SERVER_CHARACTER
#define _SERVER_CHARACTER

#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <jsoncpp/json/json.h>
#include "server_life_points.h"
#include "server_mana_points.h"
#include "server_character_class.h"
#include "server_race.h"
#include "server_inventory.h"
#include "server_item.h"
#include "server_equipment.h"
#include "server_armor.h"
#include "server_weapon.h"
#include "server_helmet.h"
#include "server_shield.h"
#include "server_movement.h"
#include "../common_collision_info.h"
#include "../common_protocol_character.h"

/* Clase que representa a un personaje del juego.
 * Es no copiable.
 */
class Character {
private:
    size_t id;
    Json::Value& config;
    Movement movement;
    CharacterClass& character_class;
    Race& race;
    LifePoints life;
    ManaPoints mana;
    Inventory inventory;
    Equipment equipment;
    CollisionInfo &collisionInfo;

    int gold;
    int level;
    bool alive;
    bool newbie;

    // No copiable.
    Character(const Character&) = delete;
    Character& operator=(const Character&) = delete;

    int drop_gold();
    void drop_items();
    const int max_secure_gold();
    const int max_gold();
    bool is_critical();
    bool evade_attack();

public:
  // Contructor, recibe el id, la vida inicial
    Character(size_t id, Json::Value& config, CharacterClass& character_class,
    Race& race, CollisionInfo &collisionInfo);

    // Devuelve el id
    size_t get_id();

    // Devuelve la mana actual del personaje
    int get_mana();

    // Devuelve la vida actual del personaje
    int get_life();

    // Le quita vida al personaje
    void take_off_life(int life_points);

    // Le quita mana al personaje
    void take_off_mana(int mana_points);

    // Recupera la mana en mana points
    void recover_mana(int mana_points);

    // Recupera la vida en life points
    void recover_life(int life_points);

    // Devuelve verdadero si el jugador esta vivo, falso si no.
    bool is_alive();

    // Dropea los items y el oro correspondiente
    void drop();

    // Dropea el item que recibe por parametro
    void drop_item(Item& item);

    // Toma una suma de oro del suelo;
    void take_gold(int amount);

    // Toma un item del suelo
    void take_item(Item& item);

    // Equipa un arma
    void equip_weapon(Weapon& item);

    // Equipa una armadura
    void equip_armor(Armor& item);

    // Equipa un escudo
    void equip_shield(Shield& item);

    // Equipa un casco
    void equip_helmet(Helmet& item);

    // Ataca a otro personaje o a un NPC
    void attack(Character& other);

    // Defiende al personaje de un ataque
    void defense(int damage);

    // Mueve el personaje hacia la derecha
    void move_right();

    // Mueve el personaje hacia la izquierda
    void move_left();

    // Mueve el personaje hacia arriba
    void move_top();

    // Mueve el personaje hacia abajo
    void move_down();

    // Getter de la posicion del cuerpo en X
    int get_body_pos_X() const;

    // Getter de la posicion del cuerpo en Y
    int get_body_pos_Y() const;

    int16_t get_race_id() const;

    int16_t get_class_id() const;

    void populate_protocol_character(ProtocolCharacter &protocolCharacter);
};


#endif //_CHARACTER
