#ifndef _SERVER_C_RECEIVER_THREAD
#define _SERVER_C_RECEIVER_THREAD

#include <stdint.h>
#include <atomic>

#include "../common_files/common_thread.h"
#include "../common_files/common_sockets.h"
#include "../common_files/common_queue.h"
#include "../common_files/common_protocol_message.h"

class SrvClientReceiverThread: public Thread {

    uint16_t client_id;
    Socket &skt;
    Queue &receiversQueue;
    std::atomic<bool> running;

    ProtocolMessage receive_msg();

    public:
        SrvClientReceiverThread(uint16_t client_id, Socket &skt, Queue &receiversQueue);


        virtual void run() override;


};


#endif
