#include "server_life_points.h"
#include "server_os_error.h"
#include <iostream>

#define FULL_LIFE_ERROR "Error: Su vida ya se encuentra llena!"

  LifePoints::LifePoints(int constitution, float class_multiplier, float race_multiplier) {
    int initial_life = this->initial_life(constitution, class_multiplier, race_multiplier);
    this->current_life = initial_life;
    this->max_life = initial_life;
  }

  void LifePoints::subtract(int life_points){
    if (current_life >= life_points)
      current_life -= life_points;
    else
      current_life = 0;
  }

  void LifePoints::add(int life_points){
    if (current_life == max_life) throw OSError(FULL_LIFE_ERROR);
    current_life += life_points;
    if (current_life >= max_life) current_life = max_life;
  }

  int LifePoints::current(){
    return current_life;
  }

  int LifePoints::initial_life(int constitution, float class_multiplier, float race_multiplier) {
    return constitution * class_multiplier * race_multiplier;
  }

