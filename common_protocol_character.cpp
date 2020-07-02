
#include <iostream>
#include <utility>
#include "common_protocol_character.h"

ProtocolCharacter::ProtocolCharacter(
        uint16_t id,
        int16_t id_race,
        int16_t id_class,
        int16_t bodyPosX, 
        int16_t bodyPosY,
        int16_t headPosX, 
        int16_t headPosY,
        int16_t velX, 
        int16_t velY,
        int16_t helmetId,
        int16_t armorId) : id(id), 
                        id_race(id_race),
                        id_class(id_class),
                        bodyPosX(bodyPosX), 
                        bodyPosY(bodyPosY), 
                        headPosX(headPosX),
                        headPosY(headPosY),
                        velX(velX), 
                        velY(velY),
                        helmetId(helmetId),
                        armorId(armorId) {}


ProtocolCharacter::ProtocolCharacter() {}



ProtocolCharacter::ProtocolCharacter(ProtocolCharacter&& other) {
    // std::cout << "Constructor por movimiento" << std::endl;
    this->id = std::move(other.id);
    this->id_race = std::move(other.id_race);
    this->id_class = std::move(other.id_class);
    this->bodyPosX = std::move(other.bodyPosX);
    this->bodyPosY = std::move(other.bodyPosY);
    this->headPosX = std::move(other.headPosX);
    this->headPosY = std::move(other.headPosY);
    this->velX = std::move(other.velX);
    this->velY = std::move(other.velY);
    this->helmetId = std::move(other.helmetId);
    this->armorId = std::move(other.armorId);
}


ProtocolCharacter& ProtocolCharacter::operator=(ProtocolCharacter&& other) {
    // std::cout << "Asignando por movimiento" << std::endl;
    this->id = std::move(other.id);
    this->id_race = std::move(other.id_race);
    this->id_class = std::move(other.id_class);
    this->bodyPosX = std::move(other.bodyPosX);
    this->bodyPosY = std::move(other.bodyPosY);
    this->headPosX = std::move(other.headPosX);
    this->headPosY = std::move(other.headPosY);
    this->velX = std::move(other.velX);
    this->velY = std::move(other.velY);
    this->helmetId = std::move(other.helmetId);
    this->armorId = std::move(other.armorId);
    return *this;
}
    
