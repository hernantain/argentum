#ifndef _SERVER_ACCEPTOR_THREAD
#define _SERVER_ACCEPTOR_THREAD

#include "common_thread.h"
#include "common_sockets.h"
#include <jsoncpp/json/json.h>
#include <atomic>
#include <stdint.h>
#include <vector>

#include "server_client.h"


class AcceptorThread: public Thread {

    Socket &acceptor_skt;
    Json::Value &config;
    std::atomic<bool> running;
    uint16_t client_id;
    std::vector<SrvClient> clients;

    public:
        AcceptorThread(Socket &acceptor_skt, Json::Value &config);

        virtual void run() override;


};




#endif
