#include "server_experience_points.h"
#include <math.h>

#define INITIAL_EXPERIENCE 0
#define INITIAL_LEVEL 1

ExperiencePoints::ExperiencePoints(int difficulty_constant, float level_multiplier) {
    this->difficulty_constant = difficulty_constant;
    this->level_multiplier = level_multiplier;
    this->current_exp = INITIAL_EXPERIENCE;
    set_new_max(INITIAL_LEVEL);
}

void ExperiencePoints::subtract(const int points) {
    if (current_exp >= points)
        current_exp -= points;
    else
        current_exp = 0;
}

void ExperiencePoints::add(const int points) {
    current_exp += points;
}

int16_t ExperiencePoints::current() const {
    return current_exp;
}

int16_t ExperiencePoints::max() const {
    return max_exp;
}

void ExperiencePoints::set_new_max(const int level) {
    int new_max_exp = difficulty_constant * (pow(level, level_multiplier));
    this->max_exp = new_max_exp;
}
