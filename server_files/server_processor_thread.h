#ifndef _SERVER_PROCESSOR_THREAD
#define _SERVER_PROCESSOR_THREAD

#include <atomic>
#include <vector>

#include "server_protocol_translator.h"
#include "common_thread.h"
#include "common_queue.h"
#include "server_client.h"
#include "server_world.h"


class ServerProcessorThread: public Thread {

    Queue &receiversQueue;
    std::vector<SrvClient> &clients;
    CollisionInfo &collisionInfo;
    Json::Value &config;
    std::atomic<bool> running;

    public:
        ServerProcessorThread(Queue &receiversQueue, std::vector<SrvClient> &clients, CollisionInfo &collisionInfo, Json::Value &config);

        virtual void run() override;


};



#endif
