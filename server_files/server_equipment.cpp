#include "server_equipment.h"
#include <iostream>

Equipment::Equipment() {}

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
