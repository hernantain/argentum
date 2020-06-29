#ifndef _SERVER_SPIDER
#define _SERVER_SPIDER

#include "server_npc.h"

/* Clase que representa a una araña del juego */
class Spider : public NPC {
private:
public:
    // Contructor
    Spider(Json::Value &config, CollisionInfo &collisionInfo);

};


#endif //_SERVER_SPIDER
