#ifndef _PROTOCOL_MESSAGE
#define _PROTOCOL_MESSAGE

#include <msgpack.hpp>

#include <stdint.h>
#include <vector>

#include "common_protocol_character.h"


struct ProtocolMessage {
    int16_t id_message;
    int16_t id_player;
    std::vector<ProtocolCharacter> characters;
    
    ProtocolMessage(int16_t id_message, int16_t id_player, ProtocolCharacter character);

    ProtocolMessage();

    ProtocolMessage(ProtocolMessage&& other);
    ProtocolMessage& operator=(ProtocolMessage&& other);

    ProtocolMessage(const ProtocolMessage&) = delete;
    ProtocolMessage& operator=(const ProtocolMessage&) = delete;

    MSGPACK_DEFINE(id_message, id_player, characters)
};


#endif
