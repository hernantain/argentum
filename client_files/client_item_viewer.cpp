
#include "client_item_viewer.h"
#include <iostream>

ItemViewer::ItemViewer(SDL_Renderer* gRenderer) {
    this->gRenderer = gRenderer;
}


bool ItemViewer::exists(uint8_t id) {
    return (items.find(id) == items.end()) ? false : true;
}


void ItemViewer::add_item(uint8_t &id) {
    std::cout << "Agregando " << (int) id << std::endl;
    LTexture* texture = new LTexture();
    texture->loadFromFile(SWORD_IMAGE, gRenderer);
    this->items.insert(std::pair<uint8_t, LTexture*>(id, texture));
}


LTexture* ItemViewer::get_item_icon(uint8_t id) {
    if (this->exists(id)) {
        // std::cout << "Existe. Toma" << std::endl;
        return this->items[id];
    } else {
        // std::cout << "No existe" << std::endl;
        this->add_item(id);
        return this->items[id];
    }
}


void ItemViewer::print_works() {
    std::cout << "ESTO FUNCIONA" << std::endl;
}