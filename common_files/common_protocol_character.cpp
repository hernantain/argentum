
#include <iostream>
#include <utility>
#include "common_protocol_character.h"


// ProtocolCharacter::ProtocolCharacter(
//         uint16_t id,
//         uint8_t id_race,
//         uint8_t id_class,
//         int16_t bodyPosX, 
//         int16_t bodyPosY,
//         int16_t orientation,
//         int16_t otherPosX,
//         int16_t otherPosY,
//         uint8_t helmetId,
//         uint8_t armorId,
//         uint8_t weaponId,
//         uint8_t shieldId,
//         int16_t life,
//         int16_t max_life,
//         int16_t mana,
//         int16_t max_mana,
//         int8_t level,
//         int16_t experience,
//         int16_t max_experience,
//         int16_t gold,
//         bool alive) : id(id), 
//                         id_race(id_race),
//                         id_class(id_class),
//                         bodyPosX(bodyPosX), 
//                         bodyPosY(bodyPosY),
//                         orientation(orientation),
//                         otherPosX(otherPosX),
//                         otherPosY(otherPosY), 
//                         helmetId(helmetId),
//                         armorId(armorId),
//                         weaponId(weaponId),
//                         shieldId(shieldId),
//                         life(life),
//                         max_life(max_life),
//                         mana(mana),
//                         max_mana(max_mana),
//                         level(level),
//                         experience(experience),
//                         max_experience(max_experience),
//                         gold(gold),
//                         alive(alive) {}


ProtocolCharacter::ProtocolCharacter(
        uint16_t id,
        int16_t bodyPosX, 
        int16_t bodyPosY,
        int16_t orientation,
        int16_t otherPosX,
        int16_t otherPosY,
        uint8_t helmetId,
        uint8_t armorId,
        uint8_t weaponId,
        uint8_t shieldId) : id(id), 
                        bodyPosX(bodyPosX), 
                        bodyPosY(bodyPosY),
                        orientation(orientation),
                        otherPosX(otherPosX),
                        otherPosY(otherPosY), 
                        helmetId(helmetId),
                        armorId(armorId),
                        weaponId(weaponId),
                        shieldId(shieldId) {
    this->id_race = 0;
    this->id_class = 0;
    this->life = 0; 
    this->max_life = 0;
    this->mana = 0; 
    this->max_mana = 0;
    this->experience = 0;
    this->max_experience = 0;
    this->alive = false;
}

ProtocolCharacter::ProtocolCharacter() {}

ProtocolCharacter::ProtocolCharacter(
    uint16_t id, 
    uint8_t id_race, 
    uint8_t id_class) : id(id), id_race(id_race), id_class(id_class) {
    this->bodyPosX = 0; 
    this->bodyPosY = 0;
    this->orientation = 0;
    this->otherPosX = 0; 
    this->otherPosY = 0;
    this->helmetId = 0;
    this->armorId = 0;
    this->weaponId = 0;
    this->shieldId = 0;
    this->life = 0; 
    this->max_life = 0;
    this->mana = 0; 
    this->max_mana = 0;
    this->experience = 0;
    this->max_experience = 0;
    this->alive = false;
}


// ProtocolCharacter::ProtocolCharacter(ProtocolCharacter&& other) {
//     // std::cout << "Constructor por movimiento" << std::endl;
//     this->id = std::move(other.id);
//     this->id_race = std::move(other.id_race);
//     this->id_class = std::move(other.id_class);
//     this->bodyPosX = std::move(other.bodyPosX);
//     this->bodyPosY = std::move(other.bodyPosY);
//     this->helmetId = std::move(other.helmetId);
//     this->armorId = std::move(other.armorId);
// }


// ProtocolCharacter& ProtocolCharacter::operator=(ProtocolCharacter&& other) {
//     // std::cout << "Asignando por movimiento" << std::endl;
//     this->id = std::move(other.id);
//     this->id_race = std::move(other.id_race);
//     this->id_class = std::move(other.id_class);
//     this->bodyPosX = std::move(other.bodyPosX);
//     this->bodyPosY = std::move(other.bodyPosY);
//     this->helmetId = std::move(other.helmetId);
//     this->armorId = std::move(other.armorId);
//     return *this;
// }
    
