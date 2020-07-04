#ifndef _PROTOCOL_CHARACTER
#define _PROTOCOL_CHARACTER

#include <msgpack.hpp>
#include <stdint.h>


struct ProtocolCharacter {
    uint16_t id;
    int16_t id_race;
    int16_t id_class;
    int16_t bodyPosX; 
    int16_t bodyPosY;
    int16_t helmetId;
    int16_t armorId;

    ProtocolCharacter(
        uint16_t id,
        int16_t id_race,
        int16_t id_class,
        int16_t bodyPosX, 
        int16_t bodyPosY,
        int16_t helmetId,
        int16_t armorId);

    ProtocolCharacter();

    // ProtocolCharacter(ProtocolCharacter&& other);
    // ProtocolCharacter& operator=(ProtocolCharacter&& other);

    // ProtocolCharacter(const ProtocolCharacter&) = delete;
    // ProtocolCharacter& operator=(const ProtocolCharacter&) = delete;

    MSGPACK_DEFINE(id, id_race, id_class, bodyPosX, bodyPosY, helmetId, armorId)
};

#endif
