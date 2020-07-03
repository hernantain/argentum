#ifndef _SERVER_CLIENT
#define _SERVER_CLIENT

#include <stdint.h>

#include "server_receiver_thread.h"
#include "server_sender_thread.h"

#include "../common_protocol_message.h"
#include "../common_queue.h"
#include "../common_sockets.h"
#include "../common_mapinfo.h"


class SrvClient {

    uint16_t client_id;
    Socket skt;
    Queue &receiversQueue;
    SrvClientReceiverThread* cReceiverThread;
    SrvClientSenderThread* cSenderThread;
    Queue messageQueue;

    public:

        SrvClient(uint16_t client_id, Socket skt, Queue &receiversQueue);

        void send_message(ProtocolMessage &updated_msg);
};




#endif
