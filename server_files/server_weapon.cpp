#include "server_weapon.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

#define NO_MANA_CONSUMPTION 0
#define DEFAULT_DAMAGE 0

Weapon::Weapon(int min_damage = DEFAULT_DAMAGE, int max_damage = DEFAULT_DAMAGE) {
    this->min_damage = min_damage;
    this->max_damage = max_damage;
    this->mana_consumption = NO_MANA_CONSUMPTION;
}

int Weapon::get_damage() {
    int damage = rand() % (max_damage - min_damage + 1) + min_damage;
    std::cout << "This weapon attacks: " << damage << std::endl;
    return damage;
}

int Weapon::is_magical() {
    return magical;
}

int Weapon::is_ranged() {
    return ranged;
}

int Weapon::get_mana_consumption() {
    return mana_consumption;
}
