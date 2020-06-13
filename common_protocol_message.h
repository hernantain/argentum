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
    

    ProtocolMessage(
        int16_t id,
        int16_t bodyPosX, 
        int16_t bodyPosY,
        int16_t headPosX,
        int16_t headPosY,
        int16_t velX, 
        int16_t velY);

    ProtocolMessage();

    // ProtocolMessage(const ProtocolMessage&) = delete;
    // ProtocolMessage& operator=(const ProtocolMessage&) = delete;
    
    // ProtocolMessage(ProtocolMessage&& other) = default;
    // ProtocolMessage& operator=(ProtocolMessage&& other) = default;

    MSGPACK_DEFINE(id, bodyPosX, bodyPosY, headPosX, headPosY, velX, velY)

};


#endif
