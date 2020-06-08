#ifndef _PROTOCOL_MESSAGE
#define _PROTOCOL_MESSAGE

#include <msgpack.hpp>
#include <stdint.h>


struct ProtocolMessage {
    uint16_t id;
    uint16_t posX; 
    uint16_t posY;
    int16_t velX;
    int16_t velY;
    

    ProtocolMessage(
        uint16_t id,
        uint16_t posX, 
        uint16_t posY,
        int16_t velX, 
        int16_t velY);

    ProtocolMessage();

    MSGPACK_DEFINE(id, posX, posY, velX, velY)

};


#endif
