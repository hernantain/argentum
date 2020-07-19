
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
    switch(id) {
        case LEATHER_ARMOR_CODE: 
            texture->loadFromFile(LEATHER_ARMOR_IMAGE, gRenderer);
            break;
        
        case PLATE_ARMOR_CODE: 
            texture->loadFromFile(PLATE_ARMOR_IMAGE, gRenderer);
            break;

        case BLUE_ROBE_CODE: 
            texture->loadFromFile(BLUE_ROBE_IMAGE, gRenderer);
            break;

        case HOOD_CODE:
            texture->loadFromFile(HOOD_IMAGE, gRenderer);
            break;

        case IRON_HELMET_CODE: 
            texture->loadFromFile(IRON_HELMET_IMAGE, gRenderer);
            break;

        case MAGIC_HAT_CODE: 
        case TURTLE_SHIELD_CODE: 
            texture->loadFromFile(TURTLE_SHIELD_IMAGE, gRenderer);
            break;

        case IRON_SHIELD_CODE: 
            texture->loadFromFile(IRON_SHIELD_IMAGE, gRenderer);
            break;

        case SWORD_CODE: 
            texture->loadFromFile(SWORD_IMAGE, gRenderer);
            break;

        case AXE_CODE: 
            texture->loadFromFile(AXE_IMAGE, gRenderer);
            break;

        case HAMMER_CODE: 
            texture->loadFromFile(HAMMER_IMAGE, gRenderer);
            break;

        case ELFIC_FLOUTE_CODE: 
            texture->loadFromFile(ELFIC_FLOUTE_IMAGE, gRenderer);
            break;

        case ASH_STAFF_CODE: 
            texture->loadFromFile(ASH_STAFF_IMAGE, gRenderer);
            break;

        case GNARLED_STAFF_CODE:
            texture->loadFromFile(GNARLED_STAFF_IMAGE, gRenderer);
            break; 

        case CRIMP_STAFF_CODE: 
            texture->loadFromFile(CRIMP_STAFF_IMAGE, gRenderer);
            break;

        case SIMPLE_BOW_CODE: 
            texture->loadFromFile(SIMPLE_BOW_IMAGE, gRenderer);
            break;

        case COMPOUND_BOW_CODE: 
            texture->loadFromFile(COMPOUND_BOW_IMAGE, gRenderer);
            break;

        case LIFE_POTION_CODE: 
            texture->loadFromFile(LIFE_POTION_IMAGE, gRenderer);
            break;

        case MANA_POTION_CODE: 
            texture->loadFromFile(MANA_POTION_IMAGE, gRenderer);
            break;

        case GOLD_CODE:
            texture->loadFromFile(GOLD_IMAGE, gRenderer);
            break;
            
    }
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


ItemViewer::~ItemViewer() {
    std::cout << "Destroying Item Viewer" << std::endl;
    std::map<uint8_t, LTexture*>::iterator itr;
    for (itr = items.begin(); itr != items.end(); ++itr)  
        itr->second->free();
}
