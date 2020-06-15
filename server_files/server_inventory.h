#ifndef _SERVER_INVENTORY
#define _SERVER_INVENTORY

#include <vector>
#include "server_item.h"

/* Clase que representa a un item del juego */
class Inventory {
private:
    std::vector<Item> items;
    unsigned int max_size;

public:
    // Contructor, recibe el tamaño del inventario
    Inventory(int size);

    // Agrega un item al inventario
    void add_item(Item& item);

    // Remueve un item del inventario
    Item remove_item();

    // Devuelve el tam del inventario
    unsigned int size();

    // Remueve un item del inventario
    bool is_full();
};


#endif //_SERVER_ITEM
