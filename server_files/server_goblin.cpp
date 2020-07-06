#include <math.h>
#include <iostream>
#include "server_goblin.h"

Goblin::Goblin(Json::Value &config, CollisionInfo &collisionInfo) : NPC(config, collisionInfo) {
    this->id = config["goblin"]["id"].asInt();
    this->level = config["goblin"]["level"].asInt();
    this->life = config["goblin"]["life"].asInt();
    this->max_life = config["goblin"]["life"].asInt();
    this->min_damage = config["goblin"]["min_damage"].asInt();
    this->max_damage = config["goblin"]["max_damage"].asInt();
    this->defense_points = config["goblin"]["defense"].asInt();    
}

