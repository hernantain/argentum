#ifndef _SERVER_SENDER_THREAD
#define _SERVER_SENDER_THREAD

#include <atomic>

#include "common_sockets.h"
#include "common_thread.h"
#include "common_queue.h"
#include "common_protocol_message.h"

class ServerSenderThread : public Thread {

    Socket &skt;
    Queue &queue;
    std::atomic<bool> running;

    void process_message(ProtocolMessage &msg);
    void process_move(ProtocolMessage &msg);
    public:
        ServerSenderThread(Socket &skt, Queue &queue);

        virtual void run() override;

};




#endif
