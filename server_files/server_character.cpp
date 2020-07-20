#include <math.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include "server_character.h"
#include "server_npc.h"

#define NO_LIFE 0
#define NO_DAMAGE 0
#define NO_GOLD 0
#define INITIAL_GOLD 0
#define INITIAL_LEVEL 1
#define CRITICAL_MULTIPLIER 2
#define LOW_CONSTANT_EXP 0
#define HIGH_CONSTANT_EXP 10

Character::Character(uint16_t id, Json::Value &config, CharacterClass character_class, Race race, CollisionInfo &collisionInfo) : 
    config(config),
    movement(collisionInfo),
    character_class(character_class),
    race(race),
    life(race.get_constitution(), character_class.get_life_multiplier(), race.get_life_multiplier()), 
    mana(race.get_intelligence(), character_class.get_mana_multiplier(), race.get_mana_multiplier()),
    experience(config["experience"]["difficulty_constant"].asUInt(), config["experience"]["level_multiplier"].asFloat()),
    inventory(config["inventory"]["max_items"].asUInt()) {
    this->id = id;
    this->gold = INITIAL_GOLD;
    this->bank_gold = INITIAL_GOLD;
    this->level = INITIAL_LEVEL;
    this->alive = true;
    this->newbie = true;
    this->meditating = false;
}

int16_t Character::get_life() const {
    return life.current();
}

int16_t Character::get_max_life() const {
    return life.max();
}

int16_t Character::get_mana() const {
    return mana.current();
}

int16_t Character::get_max_mana() const {
    return mana.max();
}

int16_t Character::get_level() const {
    return level;
}

int Character::get_width() const {
    return race.get_width();
}

int Character::get_height() const {
    return race.get_height();
}

int Character::get_gold() const {
    return gold;
}

int Character::get_bank_gold() const {
    return bank_gold;
}

bool Character::is_alive() const {
    return alive;
}

bool Character::is_newbie() const {
    return newbie;
}

bool Character::is_meditating() const {
    return meditating;
}

void Character::resurrect() {
    alive = true;
    restore_life_and_mana();
    restore_equipment();
}

void Character::restore_equipment() {
    DefaultArmor armor;
    DefaultHelmet helmet;
    DefaultWeapon weapon;
    DefaultShield shield;

    equipment.equip_armor(armor);
    equipment.equip_helmet(helmet);
    equipment.equip_weapon(weapon);
    equipment.equip_shield(shield);
}

void Character::restore_life_and_mana() {
    mana.add(get_max_mana());
    life.add(get_max_life());
}

void Character::recover_life() {
    if(!alive) return;
    life.add(race.get_recovery_factor());
}

void Character::recover_mana() {
    if(!alive) return;
    mana.add(race.get_recovery_factor());
}

void Character::take_off_life(const int life_points) {
    life.subtract(life_points);
}

void Character::take_off_mana(const int mana_points) {
    mana.subtract(mana_points);
}

void Character::meditate() {
    if (mana.is_full() || !alive) {
        meditating = false;
        return;
    }
    meditating = true;
    mana.add(character_class.get_meditation_multiplier() * race.get_intelligence());
}

bool Character::can_deposit(const int16_t posX, const int16_t posY) const {
    return alive && movement.is_near(posX, posY);
}

bool Character::can_resurrect(const int16_t posX, const int16_t posY) const {
    return !alive && movement.is_near(posX, posY);
}

int Character::deposit_gold() {
    meditating = false;
    int amount = config["gold"]["gold_amount_constant"].asInt();
    if (gold < amount) amount = gold;
    gold -= amount;
    bank_gold += amount;
    std::cout << "DepositGold::::" << amount << std::endl;
    return amount;
}

int Character::withdraw_gold() {
    meditating = false;
    int amount = config["gold"]["gold_amount_constant"].asInt();
    if (bank_gold < amount) amount = bank_gold;
    gold += amount;
    bank_gold -= amount;
    std::cout << "WithdrawingGold::::" << amount << std::endl;
    return amount;
}

bool Character::drop_item(const uint8_t id, std::vector<Item> &worldItems) {
    if (!alive || !inventory.has(id) || is_equiped(id)) return false;
    Item drop_item = inventory.drop_item(id);
    drop_item.set_posX(get_body_pos_X());
    drop_item.set_posY(get_body_pos_Y());
    worldItems.push_back(drop_item);
    return true;
}

void Character::drop_items(std::vector<Item> &worldItems) {
    int gold_drop = drop_gold();
    inventory.drop_items(get_body_pos_X(), get_body_pos_Y(), gold_drop, worldItems);
}

int Character::drop_gold() {
    if (gold > max_secure_gold()) {
        const int dropped_gold = gold - max_secure_gold();
        gold -= dropped_gold;
        std::cout << "DroppingGold:: "<< dropped_gold << std::endl;
        return dropped_gold;
    }
    return 0;
}

const int Character::max_secure_gold() const {
    return config["gold"]["secure_gold_constant"].asInt() 
    * (pow(level, config["gold"]["power_constant"].asFloat()));
}

const int Character::max_gold() const {
    const int excess = max_secure_gold() * config["gold"]["extra_gold_rate"].asFloat();
    return max_secure_gold() + excess;
}

bool Character::take_gold(const int amount) {
    if(!alive) return false;
    std::cout << "Current max gold is: "<< max_gold() << std::endl;
    std::cout << "TakingGold:: "<< amount << std::endl;
    if (gold >= max_gold()) return false;
    if (gold + amount >= max_gold()) {
        gold = max_gold();
        // drop_excess()
    } else {
        gold += amount;
    }
    return true;
}

bool Character::take_item(Item& item) {
    if(!alive) return false;
    meditating = false;
    return inventory.add_item(item);
}

void Character::equip_life_potion(Potion& item) {
    int recovery = item.get_recovery_points();
    if (inventory.has(item.get_id()) && !life.is_full()) {
        life.add(recovery);
        inventory.remove_item(item.get_id());
        std::cout << "Applying life potion::LifeNow::" << get_life() << std::endl;
    } 
}

void Character::equip_mana_potion(Potion& item) {
    int recovery = item.get_recovery_points();
    if (inventory.has(item.get_id()) && !mana.is_full()) {
        mana.add(recovery);
        inventory.remove_item(item.get_id());
        std::cout << "Applying mana potion::ManaNow::" << get_mana() << std::endl;
    } 
}

void Character::equip_weapon(Weapon& item) {
    meditating = false;
    if (inventory.has(item.get_id()) && alive) {
        equipment.equip_weapon(item);
    } 
}

void Character::equip_armor(Armor& item) {
    meditating = false;
    if (inventory.has(item.get_id()) && alive) {
        equipment.equip_armor(item);
    }
}

void Character::equip_shield(Shield& item) {
    meditating = false;
    if (inventory.has(item.get_id()) && alive) {
        equipment.equip_shield(item);
    }
}

void Character::equip_helmet(Helmet& item) {
    meditating = false;
    if (inventory.has(item.get_id()) && alive) {
        equipment.equip_helmet(item);
    }
}

int16_t Character::current_weapon() const {
    return equipment.current_weapon();
}

int16_t Character::current_armor() const {
    return equipment.current_armor();
}

int16_t Character::current_shield() const {
    return equipment.current_shield();
}

int16_t Character::current_helmet() const {
    return equipment.current_helmet();
}

bool Character::is_equiped(int16_t id) const {
    return current_helmet() == id || current_shield() == id || 
           current_armor() == id || current_weapon() == id;
}

bool Character::is_safe() const {
    return movement.is_safe();
}

bool Character::fairplay(const Attackable& other) const {
    int max_lvl_diff = config["maxAttackLvlDiff"].asInt();
    if (is_newbie() || other.is_newbie() || std::abs(level - other.get_level()) > max_lvl_diff) {
        std::cout << "Fairplay::You are newbie or the other is newbie or big diff lvl" << std::endl;
        return false;
    }
    return true;
}

bool Character::attack_zone(const Attackable& other) const {
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

bool Character::is_critical() const {
    int critical_percentage = config["attack"]["critical_probability"].asFloat() * 100;
    int critical_chances = rand() % 100 + 1;
    if (critical_chances <= critical_percentage) return true;
    return false;
}

bool Character::can_attack(const Attackable& other) const {
    if(!alive || !other.is_alive()) {
        std::cout << "CantAttack::Vos o el esta muerto" << std::endl;
        return false;
    }
    // This is commented in order to try the attack between players
    // if(!fairplay(other) || !attack_zone(other)) return false;
    if (!attack_zone(other)) return false;
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
    meditating = false;
    if(!can_attack(other)) return;
    consume_mana();
    int damage = equipment.get_weapon_damage();
    if (is_critical()) damage *= CRITICAL_MULTIPLIER;
    std::cout << "Ataque::Dano:: " << damage << std::endl;
    int final_damage = other.defense(damage);
    get_experience(other, final_damage);
    update_level();
}

bool Character::evade_attack() const {
    double evasion_chances = ((double) rand() / (RAND_MAX));
    double evasion_power = pow(evasion_chances, race.get_agility());
    bool evade = evasion_power < config["defense"]["evasion_constant"].asDouble();
    std::cout << "AtaqueEvadido::" << evade << std::endl;
    return evade;
}

int Character::defense(const int damage) {
    meditating = false;
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

int Character::experience_formula(const int enemy_level) const {
    return std::max(enemy_level - level + HIGH_CONSTANT_EXP, LOW_CONSTANT_EXP);
}

int Character::get_extra_experience(const int enemy_life, const int enemy_level) const {
    float min = config["experience"]["min_extra_probability"].asFloat();
    float max = config["experience"]["max_extra_probability"].asFloat();
    float random = ((float) rand()) / (float) RAND_MAX;
    float ponderation = min + (random * (max - min));
    int extra_exp = ponderation * enemy_life * experience_formula(enemy_level);
    std::cout << "ExtraExperienceWon:: " << extra_exp << std::endl;
    return extra_exp;
}

void Character::get_experience(const Attackable& other, const int damage) {
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

bool Character::is_near(const int posX, const int posY) const {
    return movement.is_near(posX, posY);
}

bool Character::is_attackable(const int16_t posX, const int16_t posY) const {
    return movement.is_attackable(posX, posY) && alive;
}

void Character::move_right() {
    meditating = false;
    movement.move_right(config["graphics"]["velocity"].asInt());
}

void Character::move_left() {
    meditating = false;
    movement.move_left(config["graphics"]["velocity"].asInt());
}

void Character::move_top() {
    meditating = false;
    movement.move_top(config["graphics"]["velocity"].asInt());
}

void Character::move_down() {
    meditating = false;
    movement.move_down(config["graphics"]["velocity"].asInt());
}

void Character::stop_moving() {
    movement.stop_moving();
}

int16_t Character::get_body_pos_X() const {
    return movement.get_horizontal_body_position();
}


int16_t Character::get_body_pos_Y() const {
    return movement.get_vertical_body_position();
}


int Character::get_body_facing() const { 
    return (int) movement.get_facing_direction();
}

void Character::invert_body_facing() { 
    movement.invert_body_facing();
}

void Character::populate_protocol_character(ProtocolCharacter &protocolCharacter) {
    protocolCharacter.id = this->get_id();
    protocolCharacter.id_race = this->get_race_id();
    protocolCharacter.id_class = this->get_class_id();
    protocolCharacter.bodyPosX = this->get_body_pos_X();
    protocolCharacter.bodyPosY = this->get_body_pos_Y();
    protocolCharacter.orientation = this->get_body_facing();
    protocolCharacter.mana = this->get_mana();
    protocolCharacter.max_mana = this->get_max_mana();
    protocolCharacter.life = this->get_life();
    protocolCharacter.max_life = this->get_max_life();
    protocolCharacter.experience = this->get_current_experience();
    protocolCharacter.max_experience = this->get_max_experience();
    protocolCharacter.alive = this->is_alive();
    protocolCharacter.meditating = this->is_meditating();   
  
    // protocolCharacter.otherPosX = 0;
    // protocolCharacter.otherPosY = 0;
    protocolCharacter.shieldId = this->current_shield();
    protocolCharacter.weaponId = this->current_weapon();
    protocolCharacter.helmetId = this->current_helmet();
    protocolCharacter.armorId = this->current_armor();
    // protocolCharacter.itemId = 0;
    // protocolCharacter.potionId = 0;

    // std::cout << "MANDANDO ARMOR ID: " << (int) protocolCharacter.armorId << std::endl;
    // std::cout << "PROT CHARACTER ID " << (int) protocolCharacter.id << std::endl;
    // std::cout << "PROT CHARACTER ID RACE " << (int) protocolCharacter.id_race << std::endl;
    // std::cout << "PROT CHARACTER ID CLASE " << (int) protocolCharacter.id_class << std::endl;
    // std::cout << "PROT CHARACTER bodyposX " << (int) protocolCharacter.bodyPosX << std::endl;
    // std::cout << "PROT CHARACTER bodyposY " << (int) protocolCharacter.bodyPosY << std::endl;
    // std::cout << "PROT CHARACTER ORIENTAT " << (int) protocolCharacter.orientation << std::endl;
    // std::cout << "PROT CHARACTER MANA " << (int) protocolCharacter.mana << std::endl;
    // std::cout << "PROT CHARACTER MAX_MANA " << (int) protocolCharacter.max_mana << std::endl;
    // std::cout << "PROT CHARACTER LIFE " << (int) protocolCharacter.life << std::endl;
    // std::cout << "PROT CHARACTER MAX_LIFE " << (int) protocolCharacter.max_life << std::endl;
    // std::cout << "PROT CHARACTER EXPERIEN " << (int) protocolCharacter.experience << std::endl;
    // std::cout << "PROT CHARACTER MAX EXP " << (int) protocolCharacter.max_experience << std::endl;
    // std::cout << "PROT CHARACTER ALIVE " << (int) protocolCharacter.alive << std::endl;
    // std::cout << "PROT CHARACTER MEDITATING " << (int) protocolCharacter.meditating << std::endl;
    // std::cout << std::endl;
}

uint16_t Character::get_id() const {
    return id;
}

uint8_t Character::get_race_id() const {
    return race.get_id();
}


uint8_t Character::get_class_id() const {
    return character_class.get_id();
}


int16_t Character::get_current_experience() const {
    return experience.current();
}


int16_t Character::get_max_experience() const {
    return experience.max();
}

Character::~Character() {}
