
#ifndef _SERVER
#define _SERVER

#include <atomic>
#include <jsoncpp/json/json.h>

#include "../common_sockets.h"
#include "../common_sockets.h"
#include "../common_protocol_message.h"
#include "../common_queue.h"
#include "../common_mapinfo.h"
#include "../common_collision_info.h"


#include "server_npc_thread.h"
#include "server_protocol_translator.h"
#include "server_character.h"

class Server {
    std::atomic<bool> running;
    Socket skt;
    Json::Value config;

    void initialize_config(const char* config_file);
    ProtocolMessage receive_msg(Socket skt);

    public:
        explicit Server(const char* config_file);

        void run();

        ~Server() {}
};



#endif
