
#include <iostream>
#include <utility>
#include "common_protocol_message.h"


ProtocolMessage::ProtocolMessage(
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


ProtocolMessage::ProtocolMessage() {}


ProtocolMessage::ProtocolMessage(ProtocolMessage&& other) {
    // std::cout << "Constructor por movimiento" << std::endl;
    this->id = std::move(other.id);
    this->bodyPosX = std::move(other.bodyPosX);
    this->bodyPosY = std::move(other.bodyPosY);
    this->headPosX = std::move(other.headPosX);
    this->headPosY = std::move(other.headPosY);
    this->velX = std::move(other.velX);
    this->velY = std::move(other.velY);
}


ProtocolMessage& ProtocolMessage::operator=(ProtocolMessage&& other) {
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