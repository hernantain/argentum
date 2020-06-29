#include <math.h>
#include "server_zombie.h"

Zombie::Zombie(Json::Value &config, CollisionInfo &collisionInfo) : NPC(config, collisionInfo) {
    this->id = config["zombie"]["id"].asInt();
    this->level = config["zombie"]["level"].asInt();
    this->life = config["zombie"]["life"].asInt();
    this->min_damage = config["zombie"]["min_damage"].asInt();
    this->max_damage = config["zombie"]["max_damage"].asInt();
    this->defense_points = config["zombie"]["defense"].asInt();
}

