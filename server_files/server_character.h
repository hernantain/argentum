#ifndef _SERVER_CHARACTER
#define _SERVER_CHARACTER

#include <stdlib.h>
#include "server_life_points.h"
#include "server_mana_points.h"

/* Clase que representa a un personaje del juego.
 * Es no copiable.
 */
class Character {
private:
    size_t id;
    LifePoints life;
    ManaPoints mana;
    // Movement movement;

    // No copiable.
    Character(const Character&) = delete;
    Character& operator=(const Character&) = delete;

public:
  // Contructor, recibe el id, la vida inicial
  Character(size_t id, int life, int mana);

  // Devuelve la mana actual del personaje
  int get_mana();

  // Devuelve la vida actual del personaje
  int get_life();

  // Recupera la mana en mana points
  void recover_mana(int mana_points);

  // Recupera la vida en life points
  void recover_life(int life_points);

  // Devuelve el id
  size_t get_id();
};


#endif //_CHARACTER
