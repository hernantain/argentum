#ifndef _SERVER_GOBLIN
#define _SERVER_GOBLIN

#include "server_npc.h"

/* Clase que representa a un goblin del juego */
class Goblin : public NPC {
private:
public:
    // Contructor
    Goblin(Json::Value &config, CollisionInfo &collisionInfo);
};


#endif //_SERVER_GOBLIN
