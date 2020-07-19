#include "server_helmet.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

Helmet::Helmet(int min_defense = 0, int max_defense = 0) {
    this->min_defense = min_defense;
    this->max_defense = max_defense;
}

int Helmet::get_defense() const {
    int defense = rand() % (max_defense - min_defense + 1) + min_defense;
    // std::cout << "This helmet defends: " << defense << std::endl;
    return defense;
}
