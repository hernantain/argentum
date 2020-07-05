#ifndef _PROTOCOL_MESSAGE
#define _PROTOCOL_MESSAGE

#include <msgpack.hpp>

#include <stdint.h>
#include <vector>

#include "common_protocol_character.h"
#include "common_protocol_npc.h"

struct ProtocolMessage {
    int16_t id_message;
    uint16_t id_player;
    std::vector<ProtocolCharacter> characters;
    std::vector<ProtocolNpc> npcs;

    ProtocolMessage(int16_t id_message, uint16_t id_player, ProtocolCharacter character);

    ProtocolMessage(int16_t id_message, uint16_t id_player, ProtocolNpc npc);

    ProtocolMessage();

    int find(uint16_t id);
    int find_npc(uint16_t id);
    

    ProtocolMessage(ProtocolMessage&& other);
    ProtocolMessage& operator=(ProtocolMessage&& other);

    ProtocolMessage(const ProtocolMessage&) = delete;
    ProtocolMessage& operator=(const ProtocolMessage&) = delete;

    MSGPACK_DEFINE(id_message, id_player, characters, npcs)
};


#endif
