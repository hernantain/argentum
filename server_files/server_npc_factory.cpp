#include "server_npc_factory.h"

#define GOBLIN 1
#define SKELETON 2
#define ZOMBIE 3
#define SPIDER 4

NPC* NPCFactory::make_npc(int npc_id, Json::Value& config, CollisionInfo& collisionInfo) {
    switch (npc_id) {
        case GOBLIN: return new Goblin(config, collisionInfo);
        case SKELETON: return new Skeleton(config, collisionInfo);
        case ZOMBIE: return new Zombie(config, collisionInfo);
        case SPIDER: return new Spider(config, collisionInfo);
    }
    return NULL;
}
