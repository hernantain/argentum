#ifndef _COMMON_PROTOCOL_NPC
#define _COMMON_PROTOCOL_NPC

#include <stdint.h>
#include <msgpack.hpp>


struct ProtocolNpc {
    int16_t id;
    int16_t npc_type;
    int16_t posX;
    int16_t posY;
    int16_t orientation;

    ProtocolNpc();

    ProtocolNpc(
        int16_t id,
        int16_t npc_type,
        int16_t posX,
        int16_t posY,
        int16_t orientation
    );

    MSGPACK_DEFINE(id, npc_type, posX, posY, orientation);
};


#endif
