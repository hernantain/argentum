#include "server_helmet_factory.h"

#define HOOD 4
#define IRON_HELMET 5
#define MAGIC_HAT 6

Helmet HelmetFactory::make_helmet(const uint8_t helmet_id, Json::Value& config) {
    switch (helmet_id) {
        case HOOD: return Hood(config);
        case IRON_HELMET: return IronHelmet(config);
        case MAGIC_HAT: return MagicHat(config);
    }
    return DefaultHelmet();
}
