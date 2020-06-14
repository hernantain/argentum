#include "server_life_points.h"
#include "server_os_error.h"

#define FULL_LIFE_ERROR "Error: Su vida ya se encuentra llena!"

  LifePoints::LifePoints(int life) {
    this->current_life = life;
    this->max_life = life;
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

