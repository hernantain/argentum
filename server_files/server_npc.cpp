#include <math.h>
#include <iostream>
#include <stdio.h>
#include "server_npc.h"

#define NO_LIFE 0
#define NO_DAMAGE 0
#define MIN_GOLD_MULTIPLIER 0.01
#define MAX_GOLD_MULTIPLIER 0.2

NPC::NPC(Json::Value &config, CollisionInfo &collisionInfo) : 
    config(config),
    movement(collisionInfo),
    collisionInfo(collisionInfo) {
    this->alive = true;
}

int NPC::get_id() {
    return id;
}

int NPC::get_level() {
    return level;
}

int NPC::get_life() {
    return life;
}

int NPC::get_max_life() {
    return max_life;
}

bool NPC::is_alive() {
    return alive;
}

bool NPC::is_newbie() {
    return false;
}

void NPC::drop() {
    int nothing_percentage = config["npc"]["nothing_drop_probability"].asFloat() * 100;
    int gold_percentage = config["npc"]["gold_drop_probability"].asFloat() * 100;
    int potion_percentage = config["npc"]["potion_drop_probability"].asFloat() * 100;
    int item_percentage = config["npc"]["another_item_probability"].asFloat() * 100;

    srand (time(NULL));
    int drop_chances = rand() % 100 + 1;
    if (drop_chances <= nothing_percentage) return;
    if (drop_chances <= nothing_percentage + gold_percentage) {
        // send message of drop gold
        int gold = gold_drop();
        std::cout << "Im going to drop GOLD: " << gold << std::endl;
        return;
    }
    if (drop_chances <= nothing_percentage + gold_percentage + potion_percentage) {
        // send message of drop potion
        std::cout << "Im going to drop a POTION " << std::endl;
        return;
    }
    if (drop_chances <= nothing_percentage + gold_percentage + potion_percentage + item_percentage) {
        // send message of drop item
        std::cout << "Im going to drop a ITEM " << std::endl;
        return;
    }
}

int NPC::gold_drop() {
    srand (time(NULL));
    float random = ((float) rand()) / (float) RAND_MAX;
    float gold_multiplier = random * (MAX_GOLD_MULTIPLIER - MIN_GOLD_MULTIPLIER);
    gold_multiplier += MIN_GOLD_MULTIPLIER;
    int gold_drop = gold_multiplier * life;
    return gold_drop;
}

int NPC::get_defense() {
    return defense_points;
}

int NPC::get_damage() {
    srand (time(NULL));
    int damage = rand() % (max_damage - min_damage + 1) + min_damage;
    return damage;
}

bool NPC::is_safe() {
    return movement.is_safe();
}


bool NPC::can_attack(Attackable& other) {
    if(!alive || !other.is_alive()) {
        std::cout << "NPC::CantAttack::Vos o el esta muerto" << std::endl;
        return false;
    }
    int posX = other.get_body_pos_X();
    int posY = other.get_body_pos_Y();
    std::cout << "NPC::other posX: " << posX << std::endl;
    std::cout << "NPC::other posY: " << posY << std::endl;
    return movement.is_near(posX, posY);
}

void NPC::attack(Attackable& other) {
    if(!can_attack(other)) return;
    int damage = get_damage();
    std::cout << "AtaqueNPC::Dano:: " << damage << std::endl;
    other.defense(damage);
}

int NPC::defense(int damage) {
    int defense = get_defense();
    std::cout << "Defensa:: " << defense << std::endl;
    if (damage <= defense) return NO_DAMAGE;
    int final_damage = damage - defense;
    take_off_life(final_damage);
    return final_damage;
}

void NPC::take_off_life(int life_points) {
    if (life >= life_points) {
        life -= life_points;
    } else {
        life = 0;
        alive = false;
    } 
}

bool NPC::is_near(int posX, int posY) {
    return movement.is_near(posX, posY);
}

void NPC::move_right() {
    movement.move_right(config["graphics"]["velocity"].asInt(), collisionInfo);
}

void NPC::move_left() {
    movement.move_left(config["graphics"]["velocity"].asInt(), collisionInfo);
}

void NPC::move_top() {
    movement.move_top(config["graphics"]["velocity"].asInt(), collisionInfo);
}

void NPC::move_down() {
    movement.move_down(config["graphics"]["velocity"].asInt(), collisionInfo);
}

void NPC::move_random() {
    movement.move_random(config["graphics"]["velocity"].asInt(), collisionInfo);
}

int NPC::get_body_facing() { 
    return (int) movement.get_facing_direction();
}

int NPC::get_body_pos_X() const{
    return movement.get_horizontal_body_position();
}

int NPC::get_body_pos_Y() const {
    return movement.get_vertical_body_position();
}
