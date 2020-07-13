#ifndef _CLIENT_ITEM_VIEWER
#define _CLIENT_ITEM_VIEWER

#include <stdint.h>
#include <map>
#include <SDL2/SDL.h>

#include "client_texture.h"

#define LEATHER_ARMOR_CODE 1
#define PLATE_ARMOR_CODE 2
#define BLUE_ROBE_CODE 3 // ARMORS
#define HOOD_CODE 4
#define IRON_HELMET_CODE 5
#define MAGIC_HAT_CODE 6 // HELMETS
#define TURTLE_SHIELD_CODE 7
#define IRON_SHIELD_CODE 8 // SHIELDS
#define SWORD_CODE 9
#define AXE_CODE 10
#define HAMMER_CODE 11
#define ELFIC_FLOUTE_CODE 12
#define ASH_STAFF_CODE 13
#define GNARLED_STAFF_CODE 14
#define CRIMP_STAFF_CODE 15
#define SIMPLE_BOW_CODE 16
#define COMPOUND_BOW_CODE 17 // WEAPON
#define LIFE_POTION_CODE 18
#define MANA_POTION_CODE 19 // POTION

#define BLUE_ROBE_IMAGE "images/icons/blue_robe_icon.png"
#define LEATHER_ARMOR_IMAGE "images/icons/leather_armor_icon.png"
#define PLATE_ARMOR_IMAGE "images/icons/plate_armor_icon.png"
#define MANA_POTION_IMAGE "images/icons/mana_potion_icon.png"
#define LIFE_POTION_IMAGE "images/icons/life_potion_icon.png"
#define ELFIC_FLOUTE_IMAGE "images/icons/elfic_floute_icon.png"
#define TURTLE_SHIELD_IMAGE "images/icons/turtle_shield_icon.png"
#define IRON_SHIELD_IMAGE "images/icons/iron_shield_icon.png"
#define IRON_HELMET_IMAGE "images/icons/iron_helmet_icon.png"
#define HOOD_IMAGE "images/icons/hood_icon.png"
#define COMPOUND_BOW_IMAGE "images/icons/compound_bow_icon.png"
#define SIMPLE_BOW_IMAGE "images/icons/simple_bow_icon.png"
#define AXE_IMAGE "images/icons/axe_icon.png"
#define HAMMER_IMAGE "images/icons/hammer_icon.png"
#define CRIMP_STAFF_IMAGE "images/icons/baculo_engarzado_icon.png"
#define GNARLED_STAFF_IMAGE "images/icons/baculo_nudoso_icon.png"
#define ASH_STAFF_IMAGE "images/icons/vara_fesno_icon.png"
#define SWORD_IMAGE "images/icons/sword_icon.png"

class ItemViewer {

    SDL_Renderer* gRenderer;
    std::map<uint8_t, LTexture*>items;

    bool exists(uint8_t id);
    void add_item(uint8_t &id);
    public:
        LTexture* get_item_icon(uint8_t id);    

        ItemViewer(SDL_Renderer* gRenderer);
};


#endif
