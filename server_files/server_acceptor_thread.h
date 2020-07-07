#ifndef _SERVER_ACCEPTOR_THREAD
#define _SERVER_ACCEPTOR_THREAD

#include "../common_files/common_thread.h"
#include "../common_files/common_sockets.h"
#include <jsoncpp/json/json.h>
#include <atomic>
#include <stdint.h>
#include <vector>

#include "server_client.h"
#include "server_client_manager.h"


class AcceptorThread: public Thread {

    Socket &acceptor_skt;
    Json::Value &config;
    std::atomic<bool> running;
    uint16_t client_id;
    ClientManager clientManager;

    void cleanDeadClients();
    public:
        AcceptorThread(Socket &acceptor_skt, Json::Value &config);

        virtual void run() override;


};




#endif
