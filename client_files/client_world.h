#ifndef _CLIENT_WORLD
#define _CLIENT_WORLD

#include <map>
#include <vector>
#include <SDL2/SDL.h>
#include <stdint.h>
#include <mutex>

#include "client_item_viewer.h"
#include "client_player.h"
#include "client_npc.h"
#include "client_item.h"
#include "../common_files/common_message_to_server.h"


struct ClientWorld {
    SDL_Renderer *gRenderer;
    ItemViewer &itemViewer;
    std::mutex m;

    std::map<uint16_t, Player*> players;
    std::map<uint16_t, NPC*> npcs;
    std::vector<Item*> items;

    ClientWorld(SDL_Renderer *gRenderer, ItemViewer &itemViewer);

    void add_player(uint16_t id, Player* player);
    void add_npc(uint16_t id, NPC* npc);

    void add_player(ProtocolCharacter &protocolCharacter);
    void add_npc(ProtocolNpc &protocolNpc);
    void add_item(ProtocolItem &protocolItem);

    void remove_player(uint16_t id);
    void remove_npc(int16_t id);

    void move_player(uint16_t id, int16_t newPosX, int16_t newPosY, int16_t orientation);

    void player_set_helmet(uint16_t id, uint8_t helmet_id);
    void player_set_armor(uint16_t id, uint8_t armor_id);
    void player_set_weapon(uint16_t id, uint8_t weapon_id);
    void player_set_shield(uint16_t id, uint8_t shield_id);

    void update_npcs(ProtocolMessage &msg);
    void update_player_alive_status(ProtocolMessage &msg);
    void update_dead_npcs(ProtocolMessage &msg);
    Item* update_items(ProtocolMessage &msg);
    void add_items(ProtocolMessage &msg);

    bool item_exists(ProtocolMessage &msg, unsigned int &i);
    bool item_in_world(ProtocolItem &item);
    Item* cleanItems(unsigned int i);

    void render(uint16_t id, SDL_Rect &camera, int &it);

    MessageToServer player_handle_event(uint16_t &player_id, SDL_Event& e, SDL_Rect &camera);
    MessageToServer player_handle_equip_event(uint16_t &player_id, int &itemId);

    Player* get_player(uint16_t id);

    ClientWorld(ClientWorld&& other);
    ClientWorld& operator=(ClientWorld&& other);

    ClientWorld(const ClientWorld&) = delete;
    ClientWorld& operator=(const ClientWorld&) = delete;

    ~ClientWorld();
};



#endif
