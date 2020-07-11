
#include "common_protocol_npc.h"


ProtocolNpc::ProtocolNpc() {}


ProtocolNpc::ProtocolNpc(
    int16_t id,
    int16_t npc_type,
    int16_t posX,
    int16_t posY,
    int16_t orientation) : 
                    id(id),
                    npc_type(npc_type),
                    posX(posX),
                    posY(posY),
                    orientation(orientation) {}


ProtocolNpc::ProtocolNpc(int16_t id, int16_t npc_type) : id(id), npc_type(npc_type) {}



