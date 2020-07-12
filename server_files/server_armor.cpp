#include "server_armor.h"
#include <stdlib.h>
#include <time.h>
#include <iostream> 

Armor::Armor(int min_defense = 0, int max_defense = 0) {
    this->min_defense = min_defense;
    this->max_defense = max_defense;
}

int Armor::get_defense() {
    int defense = rand() % (max_defense - min_defense + 1) + min_defense;
    std::cout << "This armor defends: " << defense << std::endl;
    return defense;
}
