#include <math.h>
#include <iostream>
#include <stdio.h>
#include "server_npc.h"

#define NO_LIFE 0
#define MIN_GOLD_MULTIPLIER 0.01
#define MAX_GOLD_MULTIPLIER 0.2

NPC::NPC(Json::Value &config, CollisionInfo &collisionInfo) : 
    config(config),
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

void NPC::attack(Character& other) {
    int damage = get_damage();
    std::cout << "AtaqueNPC::Dano:: " << damage << std::endl;
    other.defense(damage);
}

void NPC::defense(int damage) {
    int defense = get_defense();
    if (damage <= defense) return;
    int final_damage = damage - defense;
    take_off_life(final_damage);
    std::cout << "Defensa:: " << defense << std::endl;
}

void NPC::take_off_life(int life_points) {
    if (life >= life_points) {
        life -= life_points;
    } else {
        life = 0;
        alive = false;
    } 
}

void NPC::move_right(int velocity) {
    movement.move_right(velocity, collisionInfo);
}

void NPC::move_left(int velocity) {
    movement.move_left(velocity, collisionInfo);
}

void NPC::move_top(int velocity) {
    movement.move_top(velocity, collisionInfo);
}

void NPC::move_down(int velocity) {
    movement.move_down(velocity, collisionInfo);
}

int NPC::get_body_pos_X() {
    return movement.get_horizontal_body_position();
}

int NPC::get_body_pos_Y() {
    return movement.get_vertical_body_position();
}
