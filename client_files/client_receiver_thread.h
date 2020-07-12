#ifndef _CLIENT_RECEIVER_THREAD
#define _CLIENT_RECEIVER_THREAD

#include <atomic>
#include <stdint.h>

#include "client_player.h"
#include "client_world.h"
#include "client_info_view.h"
#include "../common_files/common_sockets.h"
#include "../common_files/common_thread.h"
#include "../common_files/common_protocol_message.h"


class ClientReceiverThread : public Thread {

    Socket &skt;
    ClientWorld &world;
    SDL_Rect &camera;
    InfoView &infoView;
    uint16_t player_id;
    std::atomic<bool> running;

    void process_response(ProtocolMessage &msg);
    void process_move(ProtocolMessage &msg);
    void process_equip_weapon(ProtocolMessage &msg);
    void process_equip_helmet(ProtocolMessage &msg);
    void process_equip_shield(ProtocolMessage &msg);
    void process_equip_armor(ProtocolMessage &msg);
    void process_create_player(ProtocolMessage &msg);
    void process_create_npc(ProtocolMessage &msg);
    void process_move_npcs(ProtocolMessage &msg);
    void process_recover_characters(ProtocolMessage &msg);
    void process_deposit(ProtocolMessage &msg);
    void process_meditation(ProtocolMessage &msg);
    void process_attack(ProtocolMessage &msg);
    void process_death(ProtocolMessage &msg);
    void process_log_off(ProtocolMessage &msg);
    void print_response_info(ProtocolMessage &msg);
    void process_take_item(ProtocolMessage &msg);
    void update_bars(ProtocolMessage &msg);
    
    public:
        ClientReceiverThread(Socket &skt, ClientWorld &world, SDL_Rect &camera, InfoView &infoView, uint16_t player_id);
    
        virtual void run() override;
        
};




#endif
