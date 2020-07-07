#ifndef _SERVER_NPC_THREAD
#define _SERVER_NPC_THREAD

#include <atomic>
#include <unistd.h>

#include "../common_files/common_sockets.h"
#include "../common_files/common_thread.h"
#include "../common_files/common_queue.h"
#include "../common_files/common_protocol_message.h"

class ServerNPCThread : public Thread {
    Queue &queue;
    std::atomic<bool> running;
    int max_npcs;

    public:
        ServerNPCThread(Queue &queue, int max_npcs);

        ProtocolMessage update_npcs();

        virtual void run() override;
};

#endif
