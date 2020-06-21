#ifndef _SERVER_INVENTORY
#define _SERVER_INVENTORY

#include <vector>
#include <map>
#include "server_item.h"

/* Clase que representa a un item del juego */
class Inventory {
private:
    std::map<Item, int> items;
    unsigned int max_size;

public:
    // Contructor, recibe el tamaño del inventario
    Inventory(int size);

    // Agrega un item al inventario
    void add_item(Item& item);

    // Remueve un item del inventario
    // TODO: posiblemente envie mensajes al cliente
    // Con lo cual recibiria un param mas
    void remove_item(Item& item);

    // Dropea todos los items del inventario
    // TODO: posiblemente envie mensajes al cliente
    // Con lo cual recibiria un param mas
    void drop_items();

    // Devuelve el tam del inventario
    unsigned int size();

    // Boleana, verdadera si posee el item
    bool has(Item& item);

    // Booleana, esta lleno el inventario
    bool is_full();
};


#endif //_SERVER_ITEM
