
#include <iostream>
#include <utility>
#include "common_protocol_message.h"

ProtocolMessage::ProtocolMessage(
    int16_t id_message,
    uint16_t id_player, 
    ProtocolCharacter character) : id_message(id_message),
                                   id_player(id_player) {
    this->characters.push_back(character);
}

ProtocolMessage::ProtocolMessage(
    int16_t id_message,
    uint16_t id_player, 
    ProtocolNpc npc) : id_message(id_message),
                        id_player(id_player) {
    this->npcs.push_back(std::move(npc));
}

ProtocolMessage::ProtocolMessage(
    int16_t id_message,
    uint16_t id_player, 
    ProtocolItem item) : id_message(id_message),
                        id_player(id_player) {
    this->items.push_back(std::move(item));
}

ProtocolMessage::ProtocolMessage(int16_t id_message) : id_message(id_message) {}

ProtocolMessage::ProtocolMessage() {}


ProtocolMessage::ProtocolMessage(ProtocolMessage&& other) {
    // std::cout << "Constructor por movimiento" << std::endl;
    this->id_message = other.id_message;
    this->id_player = other.id_player;
    this->characters = other.characters;
    this->npcs = other.npcs;
    this->items = other.items;
}

ProtocolMessage& ProtocolMessage::operator=(ProtocolMessage&& other) {
    // std::cout << "Asignando por movimiento" << std::endl;
    this->id_message = other.id_message;
    this->id_player = other.id_player;
    this->characters = other.characters;
    this->npcs = other.npcs;
    this->items = other.items;
    return *this;
}



int ProtocolMessage::find(uint16_t id) {
    for (unsigned int i = 0; i < characters.size(); ++i) {
        if (characters[i].id == id)
            return i;
    }
    return -1;
}

int ProtocolMessage::find_npc(uint16_t id) {
    for (unsigned int i = 0; i < npcs.size(); ++i) {
        if (npcs[i].id == id)
            return i;
    }
    return -1;
}

int ProtocolMessage::find_item(uint16_t id) {
    for (unsigned int i = 0; i < items.size(); ++i) {
        if (items[i].id == id)
            return i;
    }
    return -1;
}
