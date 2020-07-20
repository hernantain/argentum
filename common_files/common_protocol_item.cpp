
#include "common_protocol_item.h"

ProtocolItem::ProtocolItem() {}

ProtocolItem::ProtocolItem(int16_t id, int16_t posX, int16_t posY, int16_t amount) : 
    id(id),
    posX(posX),
    posY(posY),
    amount(amount) {}

