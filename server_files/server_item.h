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
    int posX;
    int posY;
    int amount;

public:
    // Contructor, recibe la cantidad de ese objeto
    Item();

    std::string get_name();

    uint8_t get_id();

    int get_amount();
    int get_posX();
    int get_posY();
    void set_amount(int item_amount);
    void set_posX(int pos);
    void set_posY(int pos);

    bool operator <(const Item& other) const {
        return id < other.id;
    }
};


#endif //_SERVER_ITEM
