#ifndef _COMMON_PROTOCOL_ITEM
#define _COMMON_PROTOCOL_ITEM

#include <stdint.h>
#include <msgpack.hpp>

struct ProtocolItem {
    int16_t id;
    int16_t posX;
    int16_t posY;
    int16_t amount;

    ProtocolItem();

    ProtocolItem(int16_t id, int16_t amount);

    ProtocolItem(
        int16_t id,
        int16_t posX,
        int16_t posY,
        int16_t amount
    );

    MSGPACK_DEFINE(id, posX, posY, amount)
};


#endif
