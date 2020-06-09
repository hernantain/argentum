#ifndef _CLIENT_RECEIVER_THREAD
#define _CLIENT_RECEIVER_THREAD

#include <atomic>

#include "client_character.h"
#include "../common_sockets.h"
#include "../common_thread.h"
#include "../common_protocol_message.h"

class ClientReceiverThread : public Thread {

    Socket &skt;
    Character &character;
    std::atomic<bool> running;

    void process_response(ProtocolMessage &msg);
    void process_move(ProtocolMessage &msg);
    public:
        ClientReceiverThread(Socket &skt, Character &character);

        virtual void run() override;
        
};




#endif
