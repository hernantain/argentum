#ifndef _SERVER_CLIENT
#define _SERVER_CLIENT


#include <stdint.h>

#include "server_client_receiver_thread.h"
#include "server_client_sender_thread.h"

#include "common_queue.h"
#include "common_sockets.h"
#include "common_mapinfo.h"


class SrvClient {

    uint16_t client_id;
    SrvClientReceiverThread* cReceiverThread;
    SrvClientSenderThread* cSenderThread;
    Socket skt;
    Queue &receiversQueue;
    MapInfo &mapInfo;
    Queue messageQueue;

    public:

        SrvClient(uint16_t client_id, Socket skt, Queue &receiversQueue, MapInfo &mapInfo);


};




#endif
