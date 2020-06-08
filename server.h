
#ifndef _SERVER
#define _SERVER

#include <atomic>

#include "common_sockets.h"


class Server {

    std::atomic<bool> running;
    Socket skt;

    public:
        Server();

        void run();
};



#endif
