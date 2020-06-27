#ifndef _PROTOCOL_MESSAGE
#define _PROTOCOL_MESSAGE

#include <msgpack.hpp>
#include <stdint.h>
#include "common_protocol_character.h"


struct ProtocolMessage {
    int16_t id;
    ProtocolCharacter character;
    
    ProtocolMessage(int16_t id, ProtocolCharacter character);

    ProtocolMessage();

    ProtocolMessage(ProtocolMessage&& other);
    ProtocolMessage& operator=(ProtocolMessage&& other);

    ProtocolMessage(const ProtocolMessage&) = delete;
    ProtocolMessage& operator=(const ProtocolMessage&) = delete;

    MSGPACK_DEFINE(id, character)

};

#endif
