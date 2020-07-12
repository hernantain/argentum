#include <math.h>
#include "server_spider.h"

Spider::Spider(Json::Value &config, CollisionInfo &collisionInfo) : NPC(config, collisionInfo) {
    this->id = config["spider"]["id"].asInt();
    this->level = config["spider"]["level"].asInt();
    this->life = config["spider"]["life"].asInt();
    this->max_life = config["spider"]["life"].asInt();
    this->min_damage = config["spider"]["min_damage"].asInt();
    this->max_damage = config["spider"]["max_damage"].asInt();
    this->defense_points = config["spider"]["defense"].asInt();
    this->width = config["spider"]["width"].asInt();   
    this->height = config["spider"]["height"].asInt();   
}

