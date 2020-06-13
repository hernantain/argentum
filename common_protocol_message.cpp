


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


// ProtocolMessage::ProtocolMessage(ProtocolMessage&& other) {
//     this->id = other.id;
//     this->bodyPosX = other.bodyPosX;
//     this->bodyPosY = other.bodyPosY;
//     this->headPosX = other.headPosX;
//     this->headPosY = other.headPosY;
//     this->velX = other.velX;
//     this->velY = other.velY;
// }


// ProtocolMessage& ProtocolMessage::operator=(ProtocolMessage&& other) {
//     this->id = other.id;
//     this->bodyPosX = other.bodyPosX;
//     this->bodyPosY = other.bodyPosY;
//     this->headPosX = other.headPosX;
//     this->headPosY = other.headPosY;
//     this->velX = other.velX;
//     this->velY = other.velY;
//     return *this;
// }