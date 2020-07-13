#include "server_armor_factory.h"

#define LEATHER_ARMOR 1
#define PLATE_ARMOR 2
#define BLUE_ROBE 3

Armor ArmorFactory::make_armor(const uint8_t armor_id, Json::Value& config) {
    switch (armor_id) {
        case LEATHER_ARMOR: return LeatherArmor(config);
        case PLATE_ARMOR: return PlateArmor(config);
    }
    return BlueRobe(config);
}
