#ifndef _PROTOCOL_MESSAGE
#define _PROTOCOL_MESSAGE

#include <msgpack.hpp>
#include <stdint.h>


struct ProtocolMessage {
    int16_t id;
    int16_t bodyPosX; 
    int16_t bodyPosY;
    int16_t headPosX;
    int16_t headPosY;
    int16_t velX;
    int16_t velY;
    int a;

    ProtocolMessage(
        int16_t id,
        int16_t bodyPosX, 
        int16_t bodyPosY,
        int16_t headPosX,
        int16_t headPosY,
        int16_t velX, 
        int16_t velY);

    ProtocolMessage();

    ProtocolMessage(ProtocolMessage&& other);
    ProtocolMessage& operator=(ProtocolMessage&& other);

    ProtocolMessage(const ProtocolMessage&) = delete;
    ProtocolMessage& operator=(const ProtocolMessage&) = delete;

    MSGPACK_DEFINE(id, bodyPosX, bodyPosY, headPosX, headPosY, velX, velY)

};


#endif
