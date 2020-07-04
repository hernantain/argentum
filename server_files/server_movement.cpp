#include "server_movement.h"
#include "server_os_error.h"
#include <iostream>

#define INITIAL_POSITION 0
#define HEAD_SIZE 20
#define CHARACTER_WIDTH 21
#define CHARACTER_HEIGHT 31
#define WINDOW_SIZE 3200


Movement::Movement() :
    bodyPosX(100), 
    bodyPosY(100) {
    // ALGORITMO CON POS RANDOM Y CHEQUEO DE COLISIONES
}


int Movement::get_horizontal_body_position() const {
    return bodyPosX;
}


int Movement::get_vertical_body_position() const {
    return bodyPosY;
}


void Movement::move_right(int velocity, CollisionInfo &collisionInfo) {
    bodyPosX += velocity;
    last_movement = RIGHT;
    check_out_of_bounds_X(velocity);
    if (check_map_collision(collisionInfo)) {
        bodyPosY -= velocity; 
    }
}

void Movement::move_left(int velocity, CollisionInfo &collisionInfo) {
    bodyPosX -= velocity;
    last_movement = LEFT;
    check_out_of_bounds_X(velocity);
    if (check_map_collision(collisionInfo)) {
        bodyPosY += velocity;
    }
}

void Movement::move_top(int velocity, CollisionInfo &collisionInfo) {
    bodyPosY -= velocity;
    last_movement = TOP;
    check_out_of_bounds_Y(velocity);
    if (check_map_collision(collisionInfo)) {
        bodyPosY += velocity;
    }
}

void Movement::move_down(int velocity, CollisionInfo &collisionInfo) {
    bodyPosY += velocity;
    last_movement = DOWN;
    check_out_of_bounds_Y(velocity);
    if (check_map_collision(collisionInfo)) {
        bodyPosY -= velocity;
    }
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
        bodyPosX -= velocity;
    }
}

void Movement::check_out_of_bounds_Y(int velocity){
    if((bodyPosY - HEAD_SIZE) < 0 || bodyPosY + CHARACTER_HEIGHT > WINDOW_SIZE) { 
        bodyPosY += velocity;
    }
}

bool Movement::check_map_collision(CollisionInfo &collisionInfo) {
    int offsetX = bodyPosX / 128;
    int offsetY = bodyPosY / 128;
    int tileNumber = (offsetY * 25) + offsetX; 
    int tile = collisionInfo.layer[tileNumber];

    if (tile == 0)
        return false;

    CollisionTile collisionTile = collisionInfo.tiles[tile];
    
    int collisionX = offsetX * 128 + collisionTile.x;
    int collisionY = offsetY * 128 + collisionTile.y;
    if ((bodyPosX + 21 > collisionX) && (bodyPosX + 21 < collisionX + collisionTile.w)) {
        return true;
    }

    if ((bodyPosX > collisionX) && (bodyPosX + 21 < collisionX + collisionTile.w)) {
        return true;
    }

    if ((bodyPosY + 31 > collisionY) && (bodyPosY + 31 < collisionY + collisionTile.h)
        && ((bodyPosX > collisionX) && (bodyPosX + 21 < collisionX + collisionTile.w))) {
        return true;
    }

    return false;
}

// TODO: this two methods
// bool Movement::can_move(){
//   return last_movement == DOWN;
// }

// bool Movement::is_colliding(){
//   return last_movement == DOWN;
// }
