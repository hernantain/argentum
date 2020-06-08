


#include "common_protocol_message.h"


ProtocolMessage::ProtocolMessage(
        uint16_t id,
        uint16_t posX, 
        uint16_t posY,
        int16_t velX, 
        int16_t velY) : id(id), posX(posX), posY(posY), velX(velX), velY(velY) {}


ProtocolMessage::ProtocolMessage() {}

