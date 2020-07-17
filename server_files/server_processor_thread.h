#ifndef _SERVER_PROCESSOR_THREAD
#define _SERVER_PROCESSOR_THREAD

#include <atomic>
#include <vector>

#include "../common_files/common_thread.h"
#include "../common_files/common_queue.h"
#include "../common_files/common_queue.h"
#include "../common_files/common_protocol_codes.h"
#include "../common_files/common_message_to_server.h"

#include "server_protocol_translator.h"
#include "server_client.h"
#include "server_world.h"
#include "server_client_manager.h"


class ServerProcessorThread: public Thread {

    Queue_2 &receiversQueue;
    ClientManager &clientManager;
    CollisionInfo &collisionInfo;
    Json::Value &config;
    std::atomic<bool> running;

    void broadcastMessage(ProtocolMessage &updated_msg);
    void addingHardcodedItems(ServerWorld &world);

    public:
        ServerProcessorThread(Queue_2 &receiversQueue, ClientManager &clientManager, CollisionInfo &collisionInfo, Json::Value &config);

        virtual void run() override;

};



#endif
