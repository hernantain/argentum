#ifndef _SERVER_NPC_THREAD
#define _SERVER_NPC_THREAD

#include <atomic>
#include <unistd.h>

#include "../common_sockets.h"
#include "../common_thread.h"
#include "../common_queue.h"
#include "../common_protocol_message.h"

class ServerNPCThread : public Thread {
    Socket &skt;
    Queue &queue;
    std::atomic<bool> running;
    int max_npcs;

    public:
        ServerNPCThread(Socket &skt, Queue &queue, int max_npcs);

        ProtocolMessage update_npcs();

        virtual void run() override;
};

#endif
