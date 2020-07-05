#include "server_equipment.h"
#include <iostream>

#define NO_DAMAGE 0
#define NO_DEFENSE 0

Equipment::Equipment() : 
    weapon(NO_DAMAGE, NO_DAMAGE), 
    shield(NO_DEFENSE, NO_DEFENSE), 
    helmet(NO_DEFENSE, NO_DEFENSE), 
    armor(NO_DEFENSE, NO_DEFENSE) {}

void Equipment::equip_weapon(Weapon& item) {
    weapon = std::move(item);
    std::cout << "Me equipe alta arma " << weapon.get_name() << std::endl;
}

void Equipment::equip_armor(Armor& item) {
    armor = std::move(item);
    std::cout << "Me equipe alta armadura " << armor.get_name() << std::endl;
}

void Equipment::equip_shield(Shield& item) {
    shield = std::move(item);
    std::cout << "Me equipe alto escudo " << shield.get_name() << std::endl;
}

void Equipment::equip_helmet(Helmet& item) {
    helmet = std::move(item);
    std::cout << "Me equipe alto casco " << helmet.get_name() << std::endl;
}

int Equipment::get_weapon_damage() {
    return weapon.get_damage();
}

bool Equipment::is_weapon_magical() {
    return weapon.is_magical();
}

bool Equipment::is_weapon_ranged() {
    return weapon.is_ranged();
}

int Equipment::get_weapon_consumption() {
    return weapon.get_mana_consumption();
}

int Equipment::get_equipment_defense() {
    int armor_defense = armor.get_defense();
    int shield_defense = shield.get_defense();
    int helmet_defense = helmet.get_defense();
    return armor_defense + shield_defense + helmet_defense;
}
