#include "server_mana_points.h"
#include "server_os_error.h"

#define FULL_MANA_ERROR "Error: Su mana ya se encuentra llena!"

  ManaPoints::ManaPoints(int life) {
    this->current_mana = life;
    this->max_mana = life;
  }

  void ManaPoints::subtract(int mana_points){
    if (current_mana >= mana_points)
      current_mana -= mana_points;
    else
      current_mana = 0;
  }

  void ManaPoints::add(int mana_points){
    if (current_mana == max_mana) throw OSError(FULL_MANA_ERROR);
    current_mana += mana_points;
    if (current_mana >= max_mana) current_mana = max_mana;
  }

  int ManaPoints::current(){
    return current_mana;
  }

