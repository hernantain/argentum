#ifndef _SERVER_CHARACTER
#define _SERVER_CHARACTER

#include <stdlib.h>
#include <jsoncpp/json/json.h>
#include "server_life_points.h"
#include "server_mana_points.h"
#include "server_inventory.h"
#include "server_item.h"
#include "server_equipment.h"
#include "server_armor.h"
#include "server_weapon.h"
#include "server_helmet.h"
#include "server_shield.h"

/* Clase que representa a un personaje del juego.
 * Es no copiable.
 */
class Character {
private:
    size_t id;
    Json::Value& config;
    // Movement movement;
    LifePoints life;
    ManaPoints mana;
    Inventory inventory;
    Equipment equipment;
    int gold;
    int level;

    // No copiable.
    Character(const Character&) = delete;
    Character& operator=(const Character&) = delete;

    int drop_gold();
    void drop_items();
    const int max_secure_gold();
    const int max_gold();

public:
  // Contructor, recibe el id, la vida inicial
  Character(size_t id, Json::Value& config, int life, int mana);

  // Devuelve la mana actual del personaje
  int get_mana();

  // Devuelve la vida actual del personaje
  int get_life();

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

  // Recupera la mana en mana points
  void recover_mana(int mana_points);

  // Recupera la vida en life points
  void recover_life(int life_points);

  // Devuelve el id
  size_t get_id();
};


#endif //_CHARACTER
