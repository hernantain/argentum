#include "server_item_factory.h"

#define LEATHER_ARMOR 1
#define PLATE_ARMOR 2
#define BLUE_ROBE 3
#define HOOD 4
#define IRON_HELMET 5
#define MAGIC_HAT 6
#define TURTLE_SHIELD 7 
#define IRON_SHIELD 8
#define SWORD 9
#define AXE 10
#define HAMMER 11
#define ELFIC_FLUTE 12
#define ASH_STAFF 13
#define GNARLED_STAFF 14
#define CRIMP_STAFF 15
#define SIMPLE_BOW 16
#define COMPOUND_BOW 17
#define LIFE_POTION 18
#define MANA_POTION 19

Item ItemFactory::make_item(const int16_t item_id, Json::Value& config) {
    switch (item_id) {
        case LEATHER_ARMOR: return LeatherArmor(config);
        case PLATE_ARMOR: return PlateArmor(config);
        case BLUE_ROBE: return BlueRobe(config);
        case HOOD: return Hood(config);
        case IRON_HELMET: return IronHelmet(config);
        case MAGIC_HAT: return MagicHat(config);
        case TURTLE_SHIELD: return TortoiseShield(config);
        case IRON_SHIELD: return IronShield(config);
        case SWORD: return Sword(config);
        case AXE: return Axe(config);
        case HAMMER: return Hammer(config);
        case ELFIC_FLUTE: return ElficFlute(config);
        case ASH_STAFF: return AshStaff(config);
        case GNARLED_STAFF: return GnarledStaff(config);
        case SIMPLE_BOW: return SimpleBow(config);
        case COMPOUND_BOW: return CompoundBow(config);
        case CRIMP_STAFF: return CrimpStaff(config);
        case LIFE_POTION: return LifePotion(config);
    }
    return ManaPotion(config);
}
