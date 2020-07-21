#include "server_equipment.h"
#include <iostream>

#define NO_DAMAGE 0
#define NO_DEFENSE 0
#define DEFAULT_EQUIPMENT 0

Equipment::Equipment() : 
    weapon(NO_DAMAGE, NO_DAMAGE), 
    shield(NO_DEFENSE, NO_DEFENSE), 
    helmet(NO_DEFENSE, NO_DEFENSE), 
    armor(NO_DEFENSE, NO_DEFENSE) {}

void Equipment::equip_weapon(Weapon& item) {
    weapon = std::move(item);
}

void Equipment::equip_armor(Armor& item) {
    armor = std::move(item);
}

void Equipment::equip_shield(Shield& item) {
    shield = std::move(item);
}

void Equipment::equip_helmet(Helmet& item) {
    helmet = std::move(item);
}

int Equipment::get_weapon_damage() const {
    return weapon.get_damage();
}

bool Equipment::is_weapon_magical() const {
    return weapon.is_magical();
}

bool Equipment::is_weapon_ranged() const {
    return weapon.is_ranged();
}

int Equipment::get_weapon_consumption() const {
    return weapon.get_mana_consumption();
}

int16_t Equipment::current_weapon() const {
    if (weapon.get_damage() > 0) return weapon.get_id();
    return DEFAULT_EQUIPMENT;
}

int16_t Equipment::current_shield() const {
    if (shield.get_defense() > 0) return shield.get_id();
    return DEFAULT_EQUIPMENT;
}

int16_t Equipment::current_armor() const {
    if (armor.get_defense() > 0) return armor.get_id();
    return DEFAULT_EQUIPMENT;
}

int16_t Equipment::current_helmet() const {
    if (helmet.get_defense() > 0) return helmet.get_id();
    return DEFAULT_EQUIPMENT;
}

int Equipment::get_equipment_defense() const {
    int armor_defense = armor.get_defense();
    int shield_defense = shield.get_defense();
    int helmet_defense = helmet.get_defense();
    return armor_defense + shield_defense + helmet_defense;
}
