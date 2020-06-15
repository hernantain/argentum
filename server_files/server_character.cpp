#include <math.h>
#include <iostream>
#include <stdio.h>
#include "server_character.h"

#define INITIAL_GOLD 0
#define INITIAL_LEVEL 1

Character::Character(size_t id, Json::Value &config, int life, int mana) 
  : config(config), life(life), mana(mana), inventory(config["inventory"]["max_items"].asUInt()) {
  this->id = id;
  this->gold = INITIAL_GOLD;
  this->level = INITIAL_LEVEL;
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

void Character::drop() {
  std::cout << "Dropping gold & items" << std::endl;
  drop_gold();
  drop_items();
}

void Character::drop_item(Item& item) {
  std::cout << "Dropping an item" << std::endl;
  inventory.remove_item(item);
}

const int Character::max_secure_gold() {
  return config["gold"]["secure_gold_constant"].asInt() 
  * (pow(level, config["gold"]["power_constant"].asFloat()));
}

const int Character::max_gold() {
  const int excess = max_secure_gold() * config["gold"]["extra_gold_rate"].asFloat();
  return max_secure_gold() + excess;
}

void Character::take_gold(int amount) {
  // TODO: We should drop the excess in this case
  std::cout << "Current max gold is: "<< max_gold() << std::endl;
  if (gold + amount >= max_gold()) {
    gold = max_gold();
    // drop_excess()
  } else {
    gold += amount;
  }
}

int Character::drop_gold() {
  // TODO: heres just the logic, we should send some message to the client, possibly
  // We are not going to return anything
  if (gold > max_secure_gold()) {
    const int dropped_gold = gold - max_secure_gold();
    gold -= dropped_gold;
    std::cout << "We are dropping gold: "<< dropped_gold << std::endl;
    return dropped_gold;
  }
  return 0;
}

void Character::take_item(Item& item) {
  // TODO: heres just the logic, we should send some message to the client
  inventory.add_item(item);
  std::cout << "Inv size: " << inventory.size() << std::endl;
}

void Character::drop_items() {
  inventory.drop_items();
}
