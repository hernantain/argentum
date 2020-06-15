#ifndef _SERVER_ITEM
#define _SERVER_ITEM

#include <string>

/* Clase que representa a un item del juego */
class Item {
private:
    std::string name;
    int amount;

public:
    // Contructor, recibe la cantidad de ese objeto
    Item(int amount);

    std::string get_name();
};


#endif //_SERVER_ITEM
