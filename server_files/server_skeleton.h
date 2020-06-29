#ifndef _SERVER_SKELETON
#define _SERVER_SKELETON

#include "server_npc.h"

/* Clase que representa a un esqueleto del juego */
class Skeleton : public NPC {
private:
public:
    // Contructor
    Skeleton(Json::Value &config, CollisionInfo &collisionInfo);

};

#endif //_SERVER_SKELETON
