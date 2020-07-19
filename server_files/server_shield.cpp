#include "server_shield.h"
#include <stdlib.h>
#include <time.h>
#include <iostream> 

Shield::Shield(int min_defense = 0, int max_defense = 0) {
    this->min_defense = min_defense;
    this->max_defense = max_defense;
}

int Shield::get_defense() {
    int defense = rand() % (max_defense - min_defense + 1) + min_defense;
    return defense;
}
