#ifndef _CLIENT_ITEM
#define _CLIENT_ITEM

#include <stdint.h>


class Item {

    uint8_t id;
    int16_t posX, posY;
    int16_t amount;

    public:
        Item(uint8_t id, int16_t posX, int16_t posY, int16_t amount);

        uint8_t get_id() const;
        int16_t get_posX() const;
        int16_t get_posY() const;
};


#endif
