#include "server_movement.h"
#include "server_os_error.h"
#include <iostream>

#define INITIAL_POSITION 0
#define CHARACTER_WIDTH 21
#define CHARACTER_HEIGHT 31
#define WINDOW_SIZE 3200

Movement::Movement() :
  bodyPosX(25), 
  bodyPosY(25), 
  headPosX(28), 
  headPosY(13) {}
  // bodyPosX(INITIAL_POSITION), 
  // bodyPosY(INITIAL_POSITION), 
  // headPosX(INITIAL_POSITION), 
  // headPosY(INITIAL_POSITION) {}

int Movement::get_horizontal_body_position() {
  return bodyPosX;
}

int Movement::get_horizontal_head_position() {
  return headPosX;
}

int Movement::get_vertical_body_position() {
  return bodyPosY;
}

int Movement::get_vertical_head_position() {
  return headPosY;
}

void Movement::move_right(int velocity) {
  bodyPosX += velocity;
  headPosX += velocity;
  last_movement = RIGHT;
  check_out_of_bounds_X(velocity);
}

void Movement::move_left(int velocity) {
  bodyPosX += velocity;
  headPosX += velocity;
  last_movement = LEFT;
  check_out_of_bounds_X(velocity);
}

void Movement::move_top(int velocity) {
  bodyPosY += velocity;
  headPosY += velocity;
  last_movement = TOP;
  check_out_of_bounds_Y(velocity);
}

void Movement::move_down(int velocity) {
  bodyPosY += velocity;
  headPosY += velocity;
  last_movement = DOWN;
  check_out_of_bounds_Y(velocity);
}

bool Movement::is_facing_right(){
  return last_movement == RIGHT;
}

bool Movement::is_facing_left(){
  return last_movement == LEFT;
}

bool Movement::is_facing_top(){
  return last_movement == TOP;
}

bool Movement::is_facing_down(){
  return last_movement == DOWN;
}

void Movement::check_out_of_bounds_X(int velocity){
  if(bodyPosX < 0 || bodyPosX + CHARACTER_WIDTH > WINDOW_SIZE) {
    std::cout << "Te estas chocando contra un costado" << std::endl;
		bodyPosX -= velocity;
    headPosX -= velocity;
  }
}

void Movement::check_out_of_bounds_Y(int velocity){
  if(headPosY < 0 || bodyPosY + CHARACTER_HEIGHT > WINDOW_SIZE) { 
    std::cout << "Te estas chocando contra un tope" << std::endl;
		bodyPosY -= velocity;
    headPosY -= velocity;
  }
}

// TODO: this two methods
// bool Movement::can_move(){
//   return last_movement == DOWN;
// }

// bool Movement::is_colliding(){
//   return last_movement == DOWN;
// }
