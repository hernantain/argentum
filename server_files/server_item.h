#ifndef _SERVER_ITEM
#define _SERVER_ITEM

#include <string>
#include <stdint.h>
#include <jsoncpp/json/json.h>

/* Clase que representa a un item del juego */
class Item {
protected:
    int16_t id;
    int16_t posX, posY, amount;
    std::string name;

public:
    // Contructor, recibe la cantidad de ese objeto
    Item();

    std::string get_name();

    int16_t get_id();
    int16_t get_amount();
    int16_t get_posX();
    int16_t get_posY();
    void set_id(int16_t new_id);
    void set_amount(int16_t item_amount);
    void set_posX(int16_t pos);
    void set_posY(int16_t pos);

    bool operator <(const Item& other) const {
        return id < other.id;
    }
};


#endif //_SERVER_ITEM
