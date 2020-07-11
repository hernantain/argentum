#ifndef _SERVER_ITEM
#define _SERVER_ITEM

#include <string>
#include <stdint.h>
#include <jsoncpp/json/json.h>

/* Clase que representa a un item del juego */
class Item {
protected:
    uint8_t id;
    std::string name;

public:
    // Contructor, recibe la cantidad de ese objeto
    Item();

    std::string get_name();

    uint8_t get_id();

    bool operator <(const Item& other) const {
        return id < other.id;
    }
};


#endif //_SERVER_ITEM
