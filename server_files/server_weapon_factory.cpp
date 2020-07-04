#include "server_weapon_factory.h"

#define SWORD 9
#define AXE 10
#define HAMMER 11
#define ELFIC_FLUTE 12
#define ASH_STAFF 13
#define GNARLED_STAFF 14
#define CRIMP_STAFF 15
#define SIMPLE_BOW 16
#define COMPOUND_BOW 17

Weapon WeaponFactory::make_weapon(const int weapon_id, Json::Value& config) {
    switch (weapon_id) {
        case SWORD: return Sword(config);
        case AXE: return Axe(config);
        case HAMMER: return Hammer(config);
        case GNARLED_STAFF: return GnarledStaff(config);
    }
    return CrimpStaff(config);
}
