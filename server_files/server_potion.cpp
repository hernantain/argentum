#include "server_potion.h"
#include <iostream> 

Potion::Potion(int recovery_points) {
    this->recovery_points = recovery_points;
}

int Potion::get_recovery_points() const {
    return recovery_points;
}
