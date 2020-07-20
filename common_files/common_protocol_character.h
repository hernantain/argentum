#ifndef _PROTOCOL_CHARACTER
#define _PROTOCOL_CHARACTER

#include <msgpack.hpp>
#include <stdint.h>


struct ProtocolCharacter {
    uint16_t id;
    uint8_t id_race;
    uint8_t id_class;
    int16_t bodyPosX; 
    int16_t bodyPosY;
    int16_t orientation;
    // int16_t otherPosX; 
    // int16_t otherPosY;
    uint8_t helmetId;
    uint8_t armorId;
    uint8_t weaponId;
    uint8_t shieldId;
    // uint8_t potionId;
    // uint8_t itemId;
    int16_t life, max_life;
    int16_t mana, max_mana;
    // int16_t level;
    int16_t experience;
    int16_t max_experience;
    // int16_t gold;
    bool alive;
    bool meditating;

    ProtocolCharacter();

    // ProtocolCharacter(ProtocolCharacter&& other);
    // ProtocolCharacter& operator=(ProtocolCharacter&& other);

    // ProtocolCharacter(const ProtocolCharacter&) = delete;
    // ProtocolCharacter& operator=(const ProtocolCharacter&) = delete;

    MSGPACK_DEFINE(id, id_race, id_class, bodyPosX, bodyPosY, orientation, 
                   helmetId, armorId, weaponId, shieldId, life, max_life, mana, 
                   max_mana, experience, max_experience, alive, meditating)
};

#endif
