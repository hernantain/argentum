#include "server_shield.h"
#include <stdlib.h> 
#include <iostream> 

Shield::Shield(int min_defense, int max_defense) {
    this->min_defense = min_defense;
    this->max_defense = max_defense;
}

int Shield::get_defense() {
    int defense = rand() % (max_defense - min_defense + 1) + min_defense;
    std::cout << "This shield defends: " << defense << std::endl;
    return defense;
}
