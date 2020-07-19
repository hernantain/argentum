#include "server_movement.h"
#include "server_os_error.h"
#include <iostream>
#include <cstdlib>

#define HEAD_SIZE 20
#define CHARACTER_WIDTH 21
#define CHARACTER_HEIGHT 31
#define MAX_OFFSET_TOLERANCE 30
#define MAX_ATTACK_OFFSET_TOLERANCE 330

Movement::Movement(CollisionInfo &collisionInfo) : collisionInfo(collisionInfo) {
    this->bodyPosX = rand() % (collisionInfo.get_map_width() - 40 + 1) + 0;
    this->bodyPosY = rand() % (collisionInfo.get_map_height() - 40 + 1) + 0;
    
    while(check_map_collision()) {
        this->bodyPosX = rand() % (collisionInfo.get_map_width() - 40 + 1) + 0;
        this->bodyPosY = rand() % (collisionInfo.get_map_height() - 40 + 1) + 0;
    }

    this->last_movement = STAND;
}


int16_t Movement::get_horizontal_body_position() const {
    return bodyPosX;
}


int16_t Movement::get_vertical_body_position() const {
    return bodyPosY;
}


void Movement::move_right(int velocity) {

    bodyPosX += velocity;
    last_movement = RIGHT;
    check_out_of_bounds_X(velocity);
    if (check_map_collision()) {
        bodyPosX -= velocity; 
    }
}

void Movement::move_left(int velocity) {
    bodyPosX -= velocity;
    last_movement = LEFT;
    check_out_of_bounds_X(-velocity);
    if (check_map_collision()) {
        bodyPosX += velocity;
    }
}

void Movement::move_top(int velocity) {
    bodyPosY -= velocity;
    last_movement = TOP;
    check_out_of_bounds_Y(-velocity);
    if (check_map_collision()) {
        bodyPosY += velocity;
    }
}

void Movement::move_down(int velocity) {
    bodyPosY += velocity;
    last_movement = DOWN;
    check_out_of_bounds_Y(velocity);
    if (check_map_collision()) {
        bodyPosY -= velocity;
    }
}

void Movement::move_random(int velocity) {
    int randNum = (rand() % 4) + 1;
    switch (randNum) {
        case 1: return move_right(velocity);
        case 2: return move_left(velocity);
        case 3: return move_top(velocity);
        case 4: return move_down(velocity);
    }
}

void Movement::move_aside(int velocity, int16_t posX) {
    int16_t diff_X = bodyPosX - posX;
    if (diff_X < 0) move_right(velocity);
    else move_left(velocity);
}

void Movement::move_vertical(int velocity, int16_t posY) {
    int16_t diff_Y = bodyPosY - posY;
    if (diff_Y < 0) move_down(velocity);
    else move_top(velocity);
}

void Movement::move_to(int velocity, int16_t posX, int16_t posY) {
    int16_t diff_X = std::abs(bodyPosX - posX);
    int16_t diff_Y = std::abs(bodyPosY - posY);
    if (diff_X > MAX_OFFSET_TOLERANCE) move_aside(velocity, posX);
    else if (diff_Y > MAX_OFFSET_TOLERANCE) move_vertical(velocity, posY);
}

void Movement::stop_moving() {
    last_movement = STAND;
}


_lastMovement Movement::get_facing_direction() const {
    return last_movement;
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

void Movement::invert_body_facing(){
    if (last_movement == DOWN) last_movement = TOP;
    if (last_movement == TOP) last_movement = DOWN;
    if (last_movement == LEFT) last_movement = RIGHT;
    if (last_movement == RIGHT) last_movement = LEFT;
}

bool Movement::is_near_X(int posX){
    int diff = std::abs(bodyPosX - posX);
    std::cout << "Diff in X " << diff << std::endl;
    return diff <= MAX_OFFSET_TOLERANCE;
}

bool Movement::is_near_Y(int posY){
    int diff = std::abs(bodyPosY - posY);
    std::cout << "Diff in Y " << diff << std::endl;
    return diff <= MAX_OFFSET_TOLERANCE;
}

bool Movement::is_near(int posX, int posY) {
    return is_near_X(posX) && is_near_Y(posY);
}

bool Movement::is_attackable_Y(int16_t posY){
    int diff = std::abs(bodyPosY - posY);
    return diff <= MAX_ATTACK_OFFSET_TOLERANCE;
}

bool Movement::is_attackable_X(int16_t posX) {
    int diff = std::abs(bodyPosX - posX);
    return diff <= MAX_ATTACK_OFFSET_TOLERANCE;
}
    
bool Movement::is_attackable(int16_t posX, int16_t posY){
    return is_attackable_X(posX) && is_attackable_Y(posY);
}

bool Movement::is_safe() {
    int offsetX = bodyPosX / collisionInfo.get_tile_width();
    int offsetY = bodyPosY / collisionInfo.get_tile_height();
    int tileNumber = (offsetY * 25) + offsetX;
    return (collisionInfo.layer1[tileNumber] == 75);
}

void Movement::check_out_of_bounds_X(int velocity){
    if(bodyPosX < 0 || bodyPosX + CHARACTER_WIDTH > collisionInfo.get_map_width()) {
        bodyPosX -= velocity;
    }
}

void Movement::check_out_of_bounds_Y(int velocity){
    if((bodyPosY - HEAD_SIZE) < 0 || bodyPosY + CHARACTER_HEIGHT > collisionInfo.get_map_height()) { 
        bodyPosY -= velocity;
    }
}


bool Movement::check_map_collision() {
    int offsetX = bodyPosX / collisionInfo.get_tile_width();
    int offsetY = bodyPosY / collisionInfo.get_tile_height();
    int tileNumber = (offsetY * 25) + offsetX; 
    int tile = collisionInfo.layer2[tileNumber];

    if (tile == 0)
        return false;

    int pos = collisionInfo.find(tile); //  tiles[tile];
    if (pos == -1)
        return false; // shouldn't happen


    int collisionX = offsetX * collisionInfo.get_tile_width() + collisionInfo.tiles[pos].x;
    int collisionY = offsetY * collisionInfo.get_tile_height() + collisionInfo.tiles[pos].y;

    if( this->bodyPosY + 31 <= collisionY ) return false;
    if( this->bodyPosY >= collisionY + collisionInfo.tiles[pos].h ) return false;
    if( this->bodyPosX + 21 <= collisionX ) return false;
    if( this->bodyPosX >= collisionX + collisionInfo.tiles[pos].w ) return false;

    return true;
}
