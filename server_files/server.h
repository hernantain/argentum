
#ifndef _SERVER
#define _SERVER

#include <atomic>
#include <jsoncpp/json/json.h>

#include "../common_sockets.h"


class Server {

    std::atomic<bool> running;
    Socket skt;
    Json::Value config;

    void initialize_config(const char* config_file);

    public:
        Server(const char* config_file);

        void run();

        ~Server() {}
};



#endif
