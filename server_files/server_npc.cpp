#include <math.h>
#include <iostream>
#include <stdio.h>
#include "server_npc.h"

#define NO_LIFE 0
#define NO_DAMAGE 0
#define MIN_GOLD_MULTIPLIER 0.01
#define MAX_GOLD_MULTIPLIER 0.2
#define MAX_ITEM_ID 19
#define GOLD_ITEM_ID 20
#define DROP_ITEM_AMOUNT 1

NPC::NPC(Json::Value &config, CollisionInfo &collisionInfo) : 
    config(config),
    movement(collisionInfo) {
    this->alive = true;
}

uint16_t NPC::get_id() const {
    return id;
}

int16_t NPC::get_level() const {
    return level;
}

int16_t NPC::get_life() const {
    return life;
}

int16_t NPC::get_max_life() const {
    return max_life;
}

int NPC::get_width() const{
    return width;
}

int NPC::get_height() const {
    return height;
}

bool NPC::is_alive() const {
    return alive;
}

bool NPC::is_newbie() const {
    return false;
}

void NPC::drop_items(std::vector<Item> &worldItems) {
    int nothing_percentage = config["npc"]["nothing_drop_probability"].asFloat() * 100;
    int gold_percentage = config["npc"]["gold_drop_probability"].asFloat() * 100;
    int potion_percentage = config["npc"]["potion_drop_probability"].asFloat() * 100;
    // int item_percentage = config["npc"]["another_item_probability"].asFloat() * 100;

    Item drop_item;
    int drop_chances = rand() % 100 + 1;
    if (drop_chances <= nothing_percentage) return;
    else if (drop_chances <= nothing_percentage + gold_percentage) {
        int gold_amount = gold_drop();
        drop_gold(drop_item, gold_amount);
    } else if (drop_chances <= nothing_percentage + gold_percentage + potion_percentage) {
        drop_potion(drop_item);
    } else {
        drop_random_item(drop_item);
    }

    if(drop_item.get_id() != GOLD_ITEM_ID) drop_item.set_amount(DROP_ITEM_AMOUNT);
    drop_item.set_posX(get_body_pos_X());
    drop_item.set_posY(get_body_pos_Y());
    worldItems.push_back(drop_item);
    std::cout << "NPC::DroppingItem ID::" << drop_item.get_id() << std::endl;    
}

void NPC::drop_gold(Item &drop_item, int gold) const {
    std::cout << "Im going to drop Gold: " << gold << std::endl;
    drop_item = ItemFactory::make_gold(gold);
    std::cout << "NPC::DroppingItem::" << drop_item.get_name() << std::endl;
}

void NPC::drop_potion(Item &drop_item) const {
    int rand_potion = rand() % 2;
    if (rand_potion == 0) {
        int16_t mana_potion_id = config["manaPotion"]["id"].asInt();
        drop_item = ItemFactory::make_item(mana_potion_id, config);
    } else {
        int16_t life_potion_id = config["lifePotion"]["id"].asInt();
        drop_item = ItemFactory::make_item(life_potion_id, config);
    }
}

void NPC::drop_random_item(Item &drop_item) const {
    int16_t random_item_id = rand() % MAX_ITEM_ID + 1;
    drop_item = ItemFactory::make_item(random_item_id, config);
    std::cout << "NPC::DroppingItem::" << drop_item.get_name() << std::endl;
}

int NPC::gold_drop() const {
    float random = ((float) rand()) / (float) RAND_MAX;
    float gold_multiplier = random * (MAX_GOLD_MULTIPLIER - MIN_GOLD_MULTIPLIER);
    gold_multiplier += MIN_GOLD_MULTIPLIER;
    int gold_drop = gold_multiplier * max_life;
    return gold_drop;
}

int NPC::get_defense() const{
    return defense_points;
}

int NPC::get_damage() const {
    int damage = rand() % (max_damage - min_damage + 1) + min_damage;
    return damage;
}

bool NPC::is_safe() const {
    return movement.is_safe();
}

bool NPC::attack_zone(const Attackable& other) const {
    if (is_safe() || other.is_safe()) {
        std::cout << "SafeZone::Your or your rival are on safe zone" << std::endl;
        return false;
    }
    return true;
}

bool NPC::can_attack(const Attackable& other) const {
    if(!alive || !other.is_alive()) {
        std::cout << "NPC::CantAttack::Vos o el esta muerto" << std::endl;
        return false;
    }
    if(!attack_zone(other)) return false;
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

int NPC::defense(const int damage) {
    int defense = get_defense();
    std::cout << "Defensa:: " << defense << std::endl;
    if (damage <= defense) return NO_DAMAGE;
    int final_damage = damage - defense;
    take_off_life(final_damage);
    return final_damage;
}

void NPC::take_off_life(const int life_points) {
    if (life >= life_points) {
        life -= life_points;
    } else {
        life = 0;
        alive = false;
    } 
}

bool NPC::is_near(const int posX, const int posY) const {
    return movement.is_near(posX, posY);
}

void NPC::move_right() {
    movement.move_right(config["npc"]["velocity"].asInt());
}

void NPC::move_left() {
    movement.move_left(config["npc"]["velocity"].asInt());
}

void NPC::move_top() {
    movement.move_top(config["npc"]["velocity"].asInt());
}

void NPC::move_down() {
    movement.move_down(config["npc"]["velocity"].asInt());
}

void NPC::move_random() {
    movement.move_random(config["npc"]["velocity"].asInt());
}

void NPC::move_to(const Attackable& other) {
    if(!attack_zone(other)) {
        move_random();
        return;
    }
    int16_t posX = other.get_body_pos_X();
    int16_t posY = other.get_body_pos_Y();
    movement.move_to(config["npc"]["velocity"].asInt(), posX, posY);
}

int NPC::get_body_facing() const { 
    return (int) movement.get_facing_direction();
}

int16_t NPC::get_body_pos_X() const {
    return movement.get_horizontal_body_position();
}

int16_t NPC::get_body_pos_Y() const {
    return movement.get_vertical_body_position();
}

NPC::~NPC() {}
