#ifndef _SERVER_C_SENDER_THREAD
#define _SERVER_C_SENDER_THREAD

#include <stdint.h>
#include <atomic>

#include "../common_thread.h"
#include "../common_sockets.h"
#include "../common_queue.h"
#include "../common_mapinfo.h"


class SrvClientSenderThread: public Thread {

    uint16_t client_id;
    Socket &skt;
    Queue &messageQueue;
    MapInfo &mapInfo;
    std::atomic<bool> running;

    public:
        SrvClientSenderThread(uint16_t client_id, Socket &skt, Queue &messageQueue, MapInfo &mapInfo);

        virtual void run() override;

};


#endif