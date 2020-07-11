#ifndef _SERVER_CHARACTER
#define _SERVER_CHARACTER

#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <jsoncpp/json/json.h>
#include "server_life_points.h"
#include "server_mana_points.h"
#include "server_experience_points.h"
#include "server_character_class.h"
#include "server_race.h"
#include "server_inventory.h"
#include "server_item.h"
#include "server_equipment.h"
#include "server_armor.h"
#include "server_weapon.h"
#include "server_helmet.h"
#include "server_shield.h"
#include "server_potion.h"
#include "server_movement.h"
#include "server_attackable.h"

#include "../common_files/common_collision_info.h"
#include "../common_files/common_protocol_character.h"

class NPC;

/* Clase que representa a un personaje del juego.
 * Es no copiable.
 */
class Character : public Attackable {
private:
    size_t id;
    Json::Value& config;
    Movement movement;
    CharacterClass character_class;
    Race race;
    LifePoints life;
    ManaPoints mana;
    ExperiencePoints experience;
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
    int experience_formula(int enemy_level);
    int get_extra_experience(int enemy_life, int enemy_level);
    void get_experience(Attackable& other, int damage);
    void update_level();
    void update_newbie();
    bool can_attack(Attackable& other);
    void consume_mana();

public:
    // Contructor, recibe el id, la vida inicial
    Character(size_t id, Json::Value& config, CharacterClass character_class,
    Race race, CollisionInfo &collisionInfo);

    // Devuelve el id
    int get_id();

    // Devuelve la mana actual del personaje
    int get_mana();

    // Devuelve la vida actual del personaje
    int get_life();

    // Devuelve la mana maxima del personaje en el nivel actual
    int get_max_mana();

    // Devuelve la vida maxima del personaje en el nivel actual
    int get_max_life();

    // Devuelve el nivel del personaje
    int get_level();

    // Devuelve un booleano que indica si el jugador es newbie o no
    bool is_newbie();

    // Resucita al personaje en cuestion
    void resurrect();

    // Restablece el nivel maximo de mana y vida del personaje
    void restore_life_and_mana();

    // Pone al jugador en estado de meditacion
    void meditate();

    // Emula el deposito de oro, devuelve una suma fija de dinero a depsitar
    int deposit_gold();

    // Emula el retiro de oro, devuelve una suma fija de dinero a depsitar
    void withdraw_gold();

    // Devuelve un booleano que indica si el jugador esta en zona segura o no.
    bool is_safe();

    // Chequea que tanto vos como el otro jugador esten en zona segura
    bool attack_zone(Attackable& other);

    // Devuelve un booleano que indica si hay fairplay o no.
    bool fairplay(Attackable& other);

    // Le quita vida al personaje
    void take_off_life(int life_points);

    // Le quita mana al personaje
    void take_off_mana(int mana_points);

    // Recupera la mana en FRazaRecuperacion puntos
    void recover_mana();

    // Recupera la vida en FRazaRecuperacion puntos
    void recover_life();

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

    // Equipa una pocion de vida
    void equip_life_potion(Potion& item);

    // Equipa una pocion de mana
    void equip_mana_potion(Potion& item);

    // Equipa un arma
    void equip_weapon(Weapon& item);

    // Equipa una armadura
    void equip_armor(Armor& item);

    // Equipa un escudo
    void equip_shield(Shield& item);

    // Equipa un casco
    void equip_helmet(Helmet& item);

    // Ataca a un NPC o a un personaje
    void attack(Attackable& other) override;

    // Defiende al personaje de un ataque. Devuelve el daño final realizado
    int defense(int damage) override;

    // Booleano que devuelve si el personaje esta cerca de la posicion
    bool is_near(int posX, int posY);

    // Mueve el personaje hacia la derecha
    void move_right();

    // Mueve el personaje hacia la izquierda
    void move_left();

    // Mueve el personaje hacia arriba
    void move_top();

    // Mueve el personaje hacia abajo
    void move_down();

    // Detiene el movimmient del personaje
    void stop_moving();

    // Getter de la posicion del cuerpo en X
    int get_body_pos_X() const;

    // Getter de la posicion del cuerpo en Y
    int get_body_pos_Y() const;

    // Getter de para donde el character apunta
    int get_body_facing();

    // Getter de la experiencia actual
    int get_current_experience();

    // Getter de la experinecia max actual
    int get_max_experience();

    int16_t get_race_id() const;

    int16_t get_class_id();

    void populate_protocol_character(ProtocolCharacter &protocolCharacter);
};


#endif //_CHARACTER
