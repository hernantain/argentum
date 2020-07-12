#include <math.h>
#include <iostream>
#include "server_skeleton.h"

Skeleton::Skeleton(Json::Value &config, CollisionInfo &collisionInfo) : NPC(config, collisionInfo) {
    this->id = config["skeleton"]["id"].asInt();
    this->level = config["skeleton"]["level"].asInt();
    this->life = config["skeleton"]["life"].asInt();
    this->max_life = config["skeleton"]["life"].asInt();
    this->min_damage = config["skeleton"]["min_damage"].asInt();
    this->max_damage = config["skeleton"]["max_damage"].asInt();
    this->defense_points = config["skeleton"]["defense"].asInt();
    this->width = config["skeleton"]["width"].asInt();   
    this->height = config["skeleton"]["height"].asInt();  
}

