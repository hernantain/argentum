
#include <iostream>
#include <utility>
#include "common_protocol_message.h"

ProtocolMessage::ProtocolMessage(
    int16_t id_message,
    uint16_t id_player, 
    ProtocolCharacter character) : id_message(id_message),
                                   id_player(id_player) {
    this->characters.push_back(std::move(character));
}

ProtocolMessage::ProtocolMessage() {}

ProtocolMessage::ProtocolMessage(ProtocolMessage&& other) {
    // std::cout << "Constructor por movimiento" << std::endl;
    this->id_message = std::move(other.id_message);
    this->id_player = std::move(other.id_player);
    this->characters = std::move(other.characters);
}

ProtocolMessage& ProtocolMessage::operator=(ProtocolMessage&& other) {
    // std::cout << "Asignando por movimiento" << std::endl;
    this->id_message = std::move(other.id_message);
    this->id_player = std::move(other.id_player);
    this->characters = std::move(other.characters);
    return *this;
}



int ProtocolMessage::find(uint16_t id) {
    for (unsigned int i = 0; i < characters.size(); ++i) {
        if (characters[i].id == id)
            return i;
    }
    return -1;
}
