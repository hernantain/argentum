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
    int16_t otherPosX; 
    int16_t otherPosY;
    int16_t helmetId;
    int16_t armorId;
    int16_t weaponId;

    ProtocolCharacter(
        uint16_t id,
        int16_t id_race,
        int16_t id_class,
        int16_t bodyPosX, 
        int16_t bodyPosY,
        int16_t otherPosX,
        int16_t otherPosY,
        int16_t helmetId,
        int16_t armorId,
        int16_t weaponId);

    ProtocolCharacter();

    // ProtocolCharacter(ProtocolCharacter&& other);
    // ProtocolCharacter& operator=(ProtocolCharacter&& other);

    // ProtocolCharacter(const ProtocolCharacter&) = delete;
    // ProtocolCharacter& operator=(const ProtocolCharacter&) = delete;

    MSGPACK_DEFINE(id, id_race, id_class, bodyPosX, bodyPosY, otherPosX, otherPosY, helmetId, armorId, weaponId)
};

#endif
