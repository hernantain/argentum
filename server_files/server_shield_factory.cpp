#include "server_shield_factory.h"

#define TURTLE_SHIELD 7 
#define IRON_SHIELD 8


Shield ShieldFactory::make_shield(const uint8_t shield_id, Json::Value& config) {
    if (shield_id == TURTLE_SHIELD) return TortoiseShield(config);
    else return IronShield(config);
}
