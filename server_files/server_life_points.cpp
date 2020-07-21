#include "server_life_points.h"

#define INITIAL_LEVEL 1

LifePoints::LifePoints(int constitution, float class_multiplier, float race_multiplier) {
    this->constitution = constitution;
    this->class_multiplier = class_multiplier;
    this->race_multiplier = race_multiplier;
    set_new_max(INITIAL_LEVEL);
}

void LifePoints::subtract(const int life_points) {
    if (current_life >= life_points)
        current_life -= life_points;
    else
        current_life = 0;
}

void LifePoints::add(const int life_points) {
    if (current_life == max_life) return;
    current_life += life_points;
    if (current_life >= max_life) current_life = max_life;
}

bool LifePoints::is_full() const {
    return current_life == max_life;
}

int16_t LifePoints::current() const {
    return current_life;
}

int16_t LifePoints::max() const {
    return max_life;
}

void LifePoints::set_new_max(const int level) {
    int new_max_life = constitution * class_multiplier * race_multiplier * level;
    this->current_life = new_max_life;
    this->max_life = new_max_life;
}
