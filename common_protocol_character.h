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
    int16_t orientation;
    int16_t otherPosX; 
    int16_t otherPosY;
    int16_t helmetId;
    int16_t armorId;
    int16_t weaponId;
    int16_t life, max_life;
    int16_t mana, max_mana;
    int16_t level;
    int16_t experience;
    int16_t max_experience;
    int16_t gold;
    bool alive;

    ProtocolCharacter(
        uint16_t id,
        int8_t id_race,
        int8_t id_class,
        int16_t bodyPosX, 
        int16_t bodyPosY,
        int16_t orientation,
        int16_t otherPosX,
        int16_t otherPosY,
        int8_t helmetId,
        int8_t armorId,
        int8_t weaponId,
        int16_t life,
        int16_t max_life,
        int16_t mana,
        int16_t max_mana,
        int8_t level,
        int16_t experience,
        int16_t max_experience,
        int16_t gold,
        bool alive);

    ProtocolCharacter();


    ProtocolCharacter(uint16_t id, int16_t id_race, int16_t id_class);

    ProtocolCharacter(
        uint16_t id,
        int8_t id_race,
        int8_t id_class,
        int16_t bodyPosX, 
        int16_t bodyPosY,
        int16_t orientation,
        int16_t otherPosX,
        int16_t otherPosY,
        int8_t helmetId,
        int8_t armorId,
        int8_t weaponId);


    // ProtocolCharacter(ProtocolCharacter&& other);
    // ProtocolCharacter& operator=(ProtocolCharacter&& other);

    // ProtocolCharacter(const ProtocolCharacter&) = delete;
    // ProtocolCharacter& operator=(const ProtocolCharacter&) = delete;

    MSGPACK_DEFINE(id, id_race, id_class, bodyPosX, bodyPosY, orientation, otherPosX, otherPosY, 
                   helmetId, armorId, weaponId, life, max_life, mana, max_mana, 
                   level, experience, max_experience, gold, alive)
};

#endif
