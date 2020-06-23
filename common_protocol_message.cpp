
#include <iostream>
#include <utility>
#include "common_protocol_message.h"

ProtocolMessage::ProtocolMessage(int16_t id, ProtocolCharacter character) : id(id) {
    this->character = std::move(character);
}

ProtocolMessage::ProtocolMessage() {}

ProtocolMessage::ProtocolMessage(ProtocolMessage&& other) {
    // std::cout << "Constructor por movimiento" << std::endl;
    this->id = std::move(other.id);
    this->character = std::move(other.character);
}

ProtocolMessage& ProtocolMessage::operator=(ProtocolMessage&& other) {
    // std::cout << "Asignando por movimiento" << std::endl;
    this->id = std::move(other.id);
    this->character = std::move(other.character);
    return *this;
}