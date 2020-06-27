#ifndef _SERVER_ITEM
#define _SERVER_ITEM

#include <string>
#include <jsoncpp/json/json.h>

/* Clase que representa a un item del juego */
class Item {
protected:
    int id;
    std::string name;

public:
    // Contructor, recibe la cantidad de ese objeto
    Item();

    std::string get_name();

    int get_id();

    bool operator <(const Item& other) const {
        return id < other.id;
    }
};


#endif //_SERVER_ITEM
