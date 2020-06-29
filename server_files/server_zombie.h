#ifndef _SERVER_ZOMBIE
#define _SERVER_ZOMBIE

#include "server_npc.h"

/* Clase que representa a una armadura del juego */
class Zombie : public NPC {
private:
public:
    // Contructor
    Zombie(Json::Value& config, CollisionInfo &collisionInfo);
};


#endif //_SERVER_ZOMBIE
