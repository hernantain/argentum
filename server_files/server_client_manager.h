#ifndef _SERVER_CLIENT_MANAGER
#define _SERVER_CLIENT_MANAGER

#include <mutex>
#include <vector>
#include "../common_files/common_protocol_message.h"
#include "../common_files/common_queue.h"
#include "../common_files/common_sockets.h"
#include "server_client.h"

class ClientManager {

    std::mutex m;
    std::vector<SrvClient*>clients;

    void cleanDeadClients();
    public:
        ClientManager();

        void add_client(uint16_t client_id, Socket &skt, MessageToServerQueue &receiversQueue);

        void broadcastMessage(ProtocolMessage &msg);


};


#endif
