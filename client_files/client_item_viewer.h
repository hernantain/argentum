#ifndef _CLIENT_ITEM_VIEWER
#define _CLIENT_ITEM_VIEWER

#include <stdint.h>
#include <map>
#include <SDL2/SDL.h>

#include "client_texture.h"
#include "../common_files/common_protocol_codes.h"

#define BLUE_ROBE_IMAGE "media/images/icons/blue_robe_icon.png"
#define LEATHER_ARMOR_IMAGE "media/images/icons/leather_armor_icon.png"
#define PLATE_ARMOR_IMAGE "media/images/icons/plate_armor_icon.png"
#define MANA_POTION_IMAGE "media/images/icons/mana_potion_icon.png"
#define LIFE_POTION_IMAGE "media/images/icons/life_potion_icon.png"
#define ELFIC_FLOUTE_IMAGE "media/images/icons/elfic_floute_icon.png"
#define TURTLE_SHIELD_IMAGE "media/images/icons/turtle_shield_icon.png"
#define IRON_SHIELD_IMAGE "media/images/icons/iron_shield_icon.png"
#define IRON_HELMET_IMAGE "media/images/icons/iron_helmet_icon.png"
#define HOOD_IMAGE "media/images/icons/hood_icon.png"
#define MAGIC_HAT_IMAGE "media/images/icons/magic_hat_icon.png" 
#define COMPOUND_BOW_IMAGE "media/images/icons/compound_bow_icon.png"
#define SIMPLE_BOW_IMAGE "media/images/icons/simple_bow_icon.png"
#define AXE_IMAGE "media/images/icons/axe_icon.png"
#define HAMMER_IMAGE "media/images/icons/hammer_icon.png"
#define CRIMP_STAFF_IMAGE "media/images/icons/baculo_engarzado_icon.png"
#define GNARLED_STAFF_IMAGE "media/images/icons/baculo_nudoso_icon.png"
#define ASH_STAFF_IMAGE "media/images/icons/vara_fresno_icon.png"
#define SWORD_IMAGE "media/images/icons/sword_icon.png"
#define GOLD_IMAGE "media/images/icons/gold_icon.png"

class ItemViewer {

    SDL_Renderer* gRenderer;
    std::map<uint8_t, LTexture*>items;

    bool exists(uint8_t id);
    void add_item(uint8_t &id);
    public:
        LTexture* get_item_icon(uint8_t id);    

        ItemViewer(SDL_Renderer* gRenderer);

        ItemViewer(ItemViewer&& other);
        ItemViewer& operator=(ItemViewer&& other);

        ItemViewer(const ItemViewer&) = delete;
        ItemViewer& operator=(const ItemViewer&) = delete;

        ~ItemViewer();
};


#endif
