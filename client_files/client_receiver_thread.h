#ifndef _CLIENT_RECEIVER_THREAD
#define _CLIENT_RECEIVER_THREAD

#include <atomic>

#include "client_drawable.h"
#include "../common_sockets.h"
#include "../common_thread.h"
#include "../common_protocol_message.h"


class ClientReceiverThread : public Thread {

    Socket &skt;
    Player &player;
    std::atomic<bool> running;

    void process_response(ProtocolMessage &msg);
    void process_move(ProtocolMessage &msg);
    public:
        ClientReceiverThread(Socket &skt, Player &player);

        virtual void run() override;
        
};




#endif
