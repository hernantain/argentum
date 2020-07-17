
#include <iostream>
#include <utility>
#include "common_protocol_character.h"


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
        uint8_t shieldId,
        uint8_t potionId,
        uint8_t itemId,
        bool alive) : id(id), 
                        bodyPosX(bodyPosX), 
                        bodyPosY(bodyPosY),
                        orientation(orientation),
                        otherPosX(otherPosX),
                        otherPosY(otherPosY), 
                        helmetId(helmetId),
                        armorId(armorId),
                        weaponId(weaponId),
                        shieldId(shieldId),
                        potionId(potionId),
                        itemId(itemId),
                        alive(alive) {
    this->id_race = 0;
    this->id_class = 0;
    this->life = 0; 
    this->max_life = 0;
    this->mana = 0; 
    this->max_mana = 0;
    this->experience = 0;
    this->max_experience = 0;
    this->meditating = false;
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
    this->potionId = 0;
    this->itemId = 0;
    this->life = 0; 
    this->max_life = 0;
    this->mana = 0; 
    this->max_mana = 0;
    this->experience = 0;
    this->max_experience = 0;
    this->alive = false;
    this->meditating = false;
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
    
