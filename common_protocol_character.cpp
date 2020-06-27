
#include <iostream>
#include <utility>
#include "common_protocol_character.h"

ProtocolCharacter::ProtocolCharacter(
        int16_t id,
        int16_t bodyPosX, 
        int16_t bodyPosY,
        int16_t headPosX, 
        int16_t headPosY,
        int16_t velX, 
        int16_t velY) : id(id), 
                        bodyPosX(bodyPosX), 
                        bodyPosY(bodyPosY), 
                        headPosX(headPosX),
                        headPosY(headPosY),
                        velX(velX), 
                        velY(velY) {}


ProtocolCharacter::ProtocolCharacter() {}

ProtocolCharacter::ProtocolCharacter(ProtocolCharacter&& other) {
    // std::cout << "Constructor por movimiento" << std::endl;
    this->id = std::move(other.id);
    this->bodyPosX = std::move(other.bodyPosX);
    this->bodyPosY = std::move(other.bodyPosY);
    this->headPosX = std::move(other.headPosX);
    this->headPosY = std::move(other.headPosY);
    this->velX = std::move(other.velX);
    this->velY = std::move(other.velY);
}

ProtocolCharacter& ProtocolCharacter::operator=(ProtocolCharacter&& other) {
    // std::cout << "Asignando por movimiento" << std::endl;
    this->id = std::move(other.id);
    this->bodyPosX = std::move(other.bodyPosX);
    this->bodyPosY = std::move(other.bodyPosY);
    this->headPosX = std::move(other.headPosX);
    this->headPosY = std::move(other.headPosY);
    this->velX = std::move(other.velX);
    this->velY = std::move(other.velY);
    return *this;
}
    
