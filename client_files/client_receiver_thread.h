#ifndef _CLIENT_RECEIVER_THREAD
#define _CLIENT_RECEIVER_THREAD

#include <atomic>
#include <stdint.h>

#include "client_player.h"
#include "client_world.h"
#include "../common_sockets.h"
#include "../common_thread.h"
#include "../common_protocol_message.h"


class ClientReceiverThread : public Thread {

    Socket &skt;
    ClientWorld &world;
    SDL_Rect &camera;
    uint16_t player_id;
    std::atomic<bool> running;

    void process_response(ProtocolMessage &msg);
    void process_move(ProtocolMessage &msg);
    void process_equip_helmet(ProtocolMessage &msg);
    void process_equip_armor(ProtocolMessage &msg);
    void process_create_player(ProtocolMessage &msg);
    public:
        ClientReceiverThread(Socket &skt, ClientWorld &world, SDL_Rect &camera, uint16_t player_id);
    
        virtual void run() override;
        
};




#endif
