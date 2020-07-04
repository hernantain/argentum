
#include <iostream>
#include <utility>
#include "common_protocol_character.h"


ProtocolCharacter::ProtocolCharacter(
        uint16_t id,
        int16_t id_race,
        int16_t id_class,
        int16_t bodyPosX, 
        int16_t bodyPosY,
        int16_t otherPosX,
        int16_t otherPosY,
        int16_t helmetId,
        int16_t armorId,
        int16_t weaponId) : id(id), 
                        id_race(id_race),
                        id_class(id_class),
                        bodyPosX(bodyPosX), 
                        bodyPosY(bodyPosY),
                        otherPosX(otherPosX),
                        otherPosY(otherPosY), 
                        helmetId(helmetId),
                        armorId(armorId),
                        weaponId(weaponId) {}


ProtocolCharacter::ProtocolCharacter() {}



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
    
