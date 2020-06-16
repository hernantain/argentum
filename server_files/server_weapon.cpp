#include "server_weapon.h"
#include <stdlib.h> 
#include <iostream> 

Weapon::Weapon(int min_damage, int max_damage) {
    this->min_damage = min_damage;
    this->max_damage = max_damage;
}

int Weapon::get_damage() {
    int damage = rand() % (max_damage - min_damage + 1) + min_damage;
    std::cout << "This weapon attacks: " << damage << std::endl;
    return damage;
}
