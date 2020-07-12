#ifndef _CLIENT_ITEM_VIEWER
#define _CLIENT_ITEM_VIEWER

#include <stdint.h>
#include <map>
#include <SDL2/SDL.h>

#include "client_texture.h"

#define LEATHER_ARMOR_CODE 1
#define PLATE_ARMOR_CODE 2
#define BLUE_ROBE_CODE 3
#define HOOD_CODE 4
#define IRON_HELMET_CODE 5
#define MAGIC_HAT_CODE 6
#define TURTLE_SHIELD_CODE 7
#define IRON_SHIELD_CODE 8
#define SWORD_CODE 9
#define AXE_CODE 10
#define HAMMER_CODE 11
#define ELFIC_FLOUTE_CODE 12
#define ASH_STAFF_CODE 13
#define GNARLED_STAFF_CODE 14
#define CRIMP_STAFF_CODE 15
#define SIMPLE_BOW_CODE 16
#define COMPOUND_BOW_CODE 17
#define LIFE_POTION_CODE 18
#define MANA_POTION_CODE 19


#define MANA_POTION_IMAGE "images/23001.png"
#define LIFE_POTION_IMAGE "images/22061.png"
#define ELFIC_FLOUTE_IMAGE "images/22036.png"
#define TURTLE_SHIELD_IMAGE "images/20013.png"
#define IRON_SHIELD_IMAGE "images/20010.png"
#define IRON_HELMET_IMAGE "images/18020.png"
#define HOOD_IMAGE "images/18017.png"
#define COMPOUND_BOW_IMAGE "images/16063.png"
#define SIMPLE_BOW_IMAGE "images/16062.png"
#define AXE_IMAGE "images/16043.png"
#define HAMMER_IMAGE "images/16030.png"
#define CRIMP_STAFF_IMAGE "images/16004.png"
#define GNARLED_STAFF_IMAGE "images/16002.png"
#define ASH_STAFF_IMAGE "images/16000.png"
#define SWORD_IMAGE "images/16099.png"

class ItemViewer {

    SDL_Renderer* gRenderer;
    std::map<uint8_t, LTexture*>items;

    bool exists(uint8_t id);

    void add_item(uint8_t &id);
    public:
        LTexture* get_item_icon(uint8_t id);    

        ItemViewer(SDL_Renderer* gRenderer);


        void print_works();
};


#endif
