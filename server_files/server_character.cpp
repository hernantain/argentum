#include "server_character.h"

Character::Character(size_t id, int life, int mana) : life(life), mana(mana) {
  this->id = id;
}

int Character::get_life() {
  return life.current();
}

int Character::get_mana() {
  return mana.current();
}

void Character::recover_mana(int mana_points) {
  mana.add(mana_points);
}

void Character::recover_life(int life_points) {
  life.add(life_points);
}
