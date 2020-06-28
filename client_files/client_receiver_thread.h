#ifndef _CLIENT_RECEIVER_THREAD
#define _CLIENT_RECEIVER_THREAD

#include <atomic>

#include "client_player.h"
#include "../common_sockets.h"
#include "../common_thread.h"
#include "../common_protocol_message.h"


class ClientReceiverThread : public Thread {

    Socket &skt;
    Player &player;
    SDL_Rect &camera;
    std::atomic<bool> running;

    void process_response(ProtocolMessage &msg);
    void process_move(ProtocolMessage &msg);
    void process_equip_helmet(ProtocolMessage &msg);
    public:
        ClientReceiverThread(Socket &skt, Player &player, SDL_Rect &camera);
    
        virtual void run() override;
        
};




#endif
