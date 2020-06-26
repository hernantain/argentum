#include "server_movement.h"
#include "server_os_error.h"

#define INITIAL_POSITION 0

Movement::Movement(int pixel_square) :
    bodyPosX(INITIAL_POSITION), 
    bodyPosY(INITIAL_POSITION), 
    headPosX(INITIAL_POSITION), 
    headPosY(INITIAL_POSITION),
    velX(INITIAL_POSITION), 
    velY(INITIAL_POSITION),
    pixel_square(pixel_square) {}

int Movement::get_horizontal_position() {
    return bodyPosX;
}

int Movement::get_vertical_position() {
    return bodyPosY;
}

int Movement::get_horizontal_velocity() {
    return velX;
}

int Movement::get_vertical_velocity() {
    return velY;
}

void Movement::move_right() {
    bodyPosX += pixel_square;
    headPosX += pixel_square;
    last_movement = RIGHT;
}

void Movement::move_left() {
    bodyPosX -= pixel_square;
    headPosX -= pixel_square;
    last_movement = LEFT;
}

void Movement::move_top() {
    bodyPosX += pixel_square;
    headPosX += pixel_square;
    last_movement = TOP;
}

void Movement::move_down() {
    bodyPosY -= pixel_square;
    headPosY -= pixel_square;
    last_movement = DOWN;
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

// TODO: this two methods
// bool Movement::can_move(){
//   return last_movement == DOWN;
// }

// bool Movement::is_colliding(){
//   return last_movement == DOWN;
// }
