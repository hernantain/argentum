#include <math.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "server_character.h"
#include "server_npc.h"

#define NO_LIFE 0
#define NO_DAMAGE 0
#define INITIAL_GOLD 0
#define INITIAL_LEVEL 1
#define CRITICAL_MULTIPLIER 2
#define LOW_CONSTANT_EXP 0
#define HIGH_CONSTANT_EXP 10

Character::Character(size_t id, Json::Value &config, CharacterClass character_class, Race race, CollisionInfo &collisionInfo) : 
    config(config),
    movement(collisionInfo),
    character_class(character_class),
    race(race),
    life(race.get_constitution(), character_class.get_life_multiplier(), race.get_life_multiplier()), 
    mana(race.get_intelligence(), character_class.get_mana_multiplier(), race.get_mana_multiplier()),
    experience(config["experience"]["difficulty_constant"].asUInt(), config["experience"]["level_multiplier"].asFloat()),
    inventory(config["inventory"]["max_items"].asUInt()),
    collisionInfo(collisionInfo) {
    this->id = id;
    this->gold = INITIAL_GOLD;
    this->level = INITIAL_LEVEL;
    this->alive = true;
    this->newbie = true;
}

int Character::get_life() {
    return life.current();
}

int Character::get_max_life() {
    return life.max();
}

int Character::get_mana() {
    return mana.current();
}

int Character::get_max_mana() {
    return mana.max();
}

int Character::get_level() {
    return level;
}

bool Character::is_alive() {
    return alive;
}

bool Character::is_newbie() {
    return newbie;
}

void Character::resurrect() {
    if (!alive) {
        alive = true;
        restore_life_and_mana();
    }
}

void Character::restore_life_and_mana() {
    mana.add(get_max_mana());
    life.add(get_max_life());
}

void Character::recover_life() {
    int recovery_factor = race.get_recovery_factor();
    std::cout << "RecoveringLife:: " << recovery_factor << std::endl;
    life.add(recovery_factor);
}

void Character::recover_mana() {
    int recovery_factor = race.get_recovery_factor();
    std::cout << "RecoveringMana:: " << recovery_factor << std::endl;
    mana.add(recovery_factor);
}

void Character::take_off_life(int life_points) {
    life.subtract(life_points);
}

void Character::take_off_mana(int mana_points) {
    mana.subtract(mana_points);
}

void Character::meditate() {
    mana.add(character_class.get_meditation_multiplier() * race.get_intelligence());
}

int Character::deposit_gold() {
    int amount = config["gold"]["gold_amount_constant"].asInt();
    if (gold < amount) amount = gold;
    gold -= amount;
    return amount;
}

void Character::withdraw_gold() {
    // TODO: think about it
    int amount = config["gold"]["gold_amount_constant"].asInt();
    gold += amount;
}

void Character::drop() {
    std::cout << "Dropping gold & items" << std::endl;
    // unequip everything;
    drop_gold();
    drop_items();
}

void Character::drop_item(Item& item) {
    std::cout << "Dropping an item" << std::endl;
    inventory.remove_item(item);
}

const int Character::max_secure_gold() {
    return config["gold"]["secure_gold_constant"].asInt() 
    * (pow(level, config["gold"]["power_constant"].asFloat()));
}

const int Character::max_gold() {
    const int excess = max_secure_gold() * config["gold"]["extra_gold_rate"].asFloat();
    return max_secure_gold() + excess;
}

void Character::take_gold(int amount) {
    // TODO: We should drop the excess in this case
    if(!alive) return;
    std::cout << "Current max gold is: "<< max_gold() << std::endl;
    if (gold + amount >= max_gold()) {
        gold = max_gold();
        // drop_excess()
    } else {
        gold += amount;
    }
}

int Character::drop_gold() {
    // TODO: heres just the logic, we should send some message to the client, possibly
    // We are not going to return anything
    if (gold > max_secure_gold()) {
        const int dropped_gold = gold - max_secure_gold();
        gold -= dropped_gold;
        std::cout << "We are dropping gold: "<< dropped_gold << std::endl;
        return dropped_gold;
    }
    return 0;
}

void Character::take_item(Item& item) {
    // TODO: heres just the logic, we should send some message to the client
    if(!alive) return;
    inventory.add_item(item);
}

void Character::drop_items() {
    inventory.drop_items();
}

void Character::equip_life_potion(Potion& item) {
    int recovery = item.get_recovery_points();
    if (inventory.has(item)) {
        life.add(recovery);
    } 
}

void Character::equip_mana_potion(Potion& item) {
    int recovery = item.get_recovery_points();
    if (inventory.has(item)) {
        mana.add(recovery);
    } 
}

void Character::equip_weapon(Weapon& item) {
    equipment.equip_weapon(item);
    // As we dont have the inventory on the UI
    // we assume we have the item
    // if (inventory.has(item)) {
    //     equipment.equip_weapon(item);
    // } 
}

void Character::equip_armor(Armor& item) {
    equipment.equip_armor(item);
    // As we dont have the inventory on the UI
    // we assume we have the item
    // if (inventory.has(item)) {
    //     equipment.equip_armor(item);
    // }
}

void Character::equip_shield(Shield& item) {
    equipment.equip_shield(item);
    // As we dont have the inventory on the UI
    // we assume we have the item
    // if (inventory.has(item)) {
    //     equipment.equip_shield(item);
    // }
}

void Character::equip_helmet(Helmet& item) {
    equipment.equip_helmet(item);
    // As we dont have the inventory on the UI
    // we assume we have the item
    // if (inventory.has(item)) {
    //     equipment.equip_helmet(item);
    // }
}

bool Character::is_safe() {
    return movement.is_safe();
}

bool Character::attack_zone(Attackable& other) {
    if (is_safe() || other.is_safe()) {
        std::cout << "SafeZone::Your or your rival are on safe zone" << std::endl;
        return false;
    }
    return true;
}

void Character::consume_mana() {
    if(!equipment.is_weapon_magical()) return;
    int mana_consumption = equipment.get_weapon_consumption();
    std::cout << "Consumiendo mana: " << mana_consumption << std::endl;
    take_off_mana(mana_consumption);
}

bool Character::is_critical() {
    int critical_percentage = config["attack"]["critical_probability"].asFloat() * 100;
    srand (time(NULL));
    int critical_chances = rand() % 100 + 1;
    if (critical_chances <= critical_percentage) return true;
    return false;
}

bool Character::can_attack(Attackable& other) {
    if(!alive || !other.is_alive()) {
        std::cout << "CantAttack::Vos o el esta muerto" << std::endl;
        return false;
    }
    // This is commented in order to try the attack between players
    // if(!fairplay(other) || !attack_zone(other)) return false;
    if (!equipment.is_weapon_ranged()) {
        int posX = other.get_body_pos_X();
        int posY = other.get_body_pos_Y();
        std::cout << "other posX: " << posX << std::endl;
        std::cout << "other posY: " << posY << std::endl;
        return movement.is_near(posX, posY);
    }
    if (equipment.is_weapon_magical() && equipment.get_weapon_consumption() > get_mana()) {
        std::cout << "CantAttack::No te da la mana" << std::endl;
        return false;
    }
    return true;
}

void Character::attack(Attackable& other) {
    if(!can_attack(other)) return;
    consume_mana();
    int damage = equipment.get_weapon_damage();
    if (is_critical()) damage *= CRITICAL_MULTIPLIER;
    std::cout << "Ataque::Dano:: " << damage << std::endl;
    int final_damage = other.defense(damage);
    get_experience(other, final_damage);
    update_level();
}

bool Character::evade_attack() {
    srand (time(NULL));
    double evasion_chances = ((double) rand() / (RAND_MAX));
    double evasion_power = pow(evasion_chances, race.get_agility());
    bool evade = evasion_power < config["defense"]["evasion_constant"].asDouble();
    std::cout << "AtaqueEvadido::" << evade << std::endl;
    return evade;
}

int Character::defense(int damage) {
    if (evade_attack()) return NO_DAMAGE;
    int defense = equipment.get_equipment_defense();
    std::cout << "Defensa:: " << defense << std::endl;
    if (damage <= defense) return NO_DAMAGE;
    int final_damage = damage - defense;
    std::cout << "Defensa::FinalDamage " << final_damage << std::endl;
    take_off_life(final_damage);
    if (life.current() == NO_LIFE) alive = false;
    return final_damage;
}

int Character::experience_formula(int enemy_level) {
    return std::max(enemy_level - level + HIGH_CONSTANT_EXP, LOW_CONSTANT_EXP);
}

int Character::get_extra_experience(int enemy_life, int enemy_level) {
    srand (time(NULL));
    float min = config["experience"]["min_extra_probability"].asFloat();
    float max = config["experience"]["max_extra_probability"].asFloat();
    float random = ((float) rand()) / (float) RAND_MAX;
    float ponderation = min + (random * (max - min));
    int extra_exp = ponderation * enemy_life * experience_formula(enemy_level);
    std::cout << "ExtraExperienceWon:: " << extra_exp << std::endl;
    return extra_exp;
}

void Character::get_experience(Attackable& other, int damage) {
    int enemy_level = other.get_level();
    int enemy_life = other.get_max_life();
    int won_experience = damage * experience_formula(enemy_level);
    std::cout << "ExperienceWon:: " << won_experience << std::endl;
    if (!other.is_alive()) {
        won_experience += get_extra_experience(enemy_life, enemy_level);
    }
    experience.add(won_experience);
}

void Character::update_level() {
    while (experience.current() >= experience.max()) {
        level++;
        std::cout << "LevelUp:: " << level << std::endl;
        life.set_new_max(level);
        mana.set_new_max(level);
        update_newbie();
        experience.subtract(experience.max());
        experience.set_new_max(level);
    }
}

void Character::update_newbie() {
    int newbie_limit = config["newbieLimit"].asInt();
    if (level > newbie_limit) {
        newbie = false;
    }
}

bool Character::is_near(int posX, int posY) {
    return movement.is_near(posX, posY);
}

void Character::move_right() {
    movement.move_right(config["graphics"]["velocity"].asInt(), collisionInfo);
}

void Character::move_left() {
    movement.move_left(config["graphics"]["velocity"].asInt(), collisionInfo);
}

void Character::move_top() {
    movement.move_top(config["graphics"]["velocity"].asInt(), collisionInfo);
}

void Character::move_down() {
    movement.move_down(config["graphics"]["velocity"].asInt(), collisionInfo);
}

void Character::stop_moving() {
    movement.stop_moving();
}

int Character::get_body_pos_X() const {
    return movement.get_horizontal_body_position();
}


int Character::get_body_pos_Y() const {
    return movement.get_vertical_body_position();
}


int Character::get_body_facing() { 
    return (int) movement.get_facing_direction();
}


void Character::populate_protocol_character(ProtocolCharacter &protocolCharacter) {
    protocolCharacter.id = this->id;
    protocolCharacter.bodyPosX = this->get_body_pos_X();
    protocolCharacter.bodyPosY = this->get_body_pos_Y();
    protocolCharacter.orientation = this->get_body_facing();
    protocolCharacter.mana = this->get_mana();
    protocolCharacter.max_mana = this->get_max_mana();
    protocolCharacter.life = this->get_life();
    protocolCharacter.max_life = this->get_max_life();
    protocolCharacter.id_race = this->get_race_id();
    protocolCharacter.id_class = this->get_class_id();
    protocolCharacter.alive = this->is_alive();
}


size_t Character::get_id() {
    return id;
}


int16_t Character::get_race_id() const {
    return race.get_id();
}


int16_t Character::get_class_id() {
    return character_class.get_id();
}
