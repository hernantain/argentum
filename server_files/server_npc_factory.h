#ifndef _NPC_FACTORY_H
#define _NPC_FACTORY_H

#include <jsoncpp/json/json.h>

#include "server_npc.h"
#include "server_zombie.h"
#include "server_spider.h"
#include "server_skeleton.h"
#include "server_goblin.h"

/* Clase que funciona como factory para los distintos tipos de NPC de la aplicacion */
class NPCFactory {
public:

    /* Recibiendo un id crea al npc correspondiente */
    static NPC* make_npc(int npc_id, Json::Value& config, CollisionInfo& collisionInfo);
};

#endif // _NPC_FACTORY_H
