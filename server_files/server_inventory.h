#ifndef _SERVER_INVENTORY
#define _SERVER_INVENTORY

#include <vector>
#include "server_item.h"
#include "server_gold.h"

/* Clase que representa a un item del juego */
class Inventory {
private:
    std::vector<Item> items;
    unsigned int max_size;

    // Dropea el oro del personaje
    void drop_gold(int16_t posX, int16_t posY, int gold, std::vector<Item> &worldItems);
public:
    // Contructor, recibe el tamaño del inventario
    explicit Inventory(int size);

    // Remueve un item al inventario
    void remove_item(const uint8_t id);

    // Agrega un item al inventario
    bool add_item(Item& item);

    // Droppea un item del inventario
    Item drop_item(const uint8_t id);

    // Dropea todos los items del inventario populando el mundo de items
    // Y recibiendo las posiciones del jugador como parametro y la cantidad de oro
    void drop_items(int16_t posX, int16_t posY, int gold, std::vector<Item> &worldItems);

    // Devuelve el tam del inventario
    unsigned int size() const;

    // Boleana, verdadera si posee el item
    bool has(const int16_t id);

    // Devuelve el indice del item si esta en el inventario, -1 si no
    int find(const int16_t id) const;

    // Booleana, esta lleno el inventario
    bool is_full() const;
};


#endif //_SERVER_ITEM
