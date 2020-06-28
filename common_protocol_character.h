#ifndef _PROTOCOL_CHARACTER
#define _PROTOCOL_CHARACTER

#include <msgpack.hpp>
#include <stdint.h>

struct ProtocolCharacter {
    int16_t id;
    int16_t bodyPosX; 
    int16_t bodyPosY;
    int16_t headPosX;
    int16_t headPosY;
    int16_t velX;
    int16_t velY;
    int16_t helmetId;
    int16_t armorId;

    ProtocolCharacter(
        int16_t id,
        int16_t bodyPosX, 
        int16_t bodyPosY,
        int16_t headPosX,
        int16_t headPosY,
        int16_t velX, 
        int16_t velY,
        int16_t helmetId,
        int16_t armorId);

    ProtocolCharacter();

    ProtocolCharacter(ProtocolCharacter&& other);
    ProtocolCharacter& operator=(ProtocolCharacter&& other);

    ProtocolCharacter(const ProtocolCharacter&) = delete;
    ProtocolCharacter& operator=(const ProtocolCharacter&) = delete;

    MSGPACK_DEFINE(id, bodyPosX, bodyPosY, headPosX, headPosY, velX, velY, helmetId, armorId)
};

#endif
