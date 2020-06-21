#include "server_weapon.h"
#include <stdlib.h>
#include <time.h>
#include <iostream> 

Weapon::Weapon(int min_damage = 0, int max_damage = 0) {
    this->min_damage = min_damage;
    this->max_damage = max_damage;
}

int Weapon::get_damage() {
    srand (time(NULL));
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
