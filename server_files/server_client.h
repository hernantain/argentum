#ifndef _SERVER_CLIENT
#define _SERVER_CLIENT

#include <stdint.h>
#include <atomic>

#include "server_receiver_thread.h"
#include "server_sender_thread.h"

#include "../common_files/common_protocol_message.h"
#include "../common_files/common_queue.h"
#include "../common_files/common_sockets.h"
#include "../common_files/common_mapinfo.h"


class SrvClient {

    uint16_t client_id;
    Socket skt;
    MessageToServerQueue &receiversQueue;
    std::atomic<bool> active;
    SrvClientReceiverThread* cReceiverThread;
    SrvClientSenderThread* cSenderThread;
    Queue messageQueue;

    public:

        SrvClient(uint16_t client_id, Socket skt, MessageToServerQueue &receiversQueue);

        void send_message(ProtocolMessage &updated_msg);

        bool is_active();

        ~SrvClient();
};




#endif
