#ifndef _SERVER_C_RECEIVER_THREAD
#define _SERVER_C_RECEIVER_THREAD

#include <stdint.h>
#include <atomic>

#include "../common_files/common_thread.h"
#include "../common_files/common_sockets.h"
#include "../common_files/common_queue.h"
#include "../common_files/common_protocol_message.h"
#include "../common_files/common_message_to_server.h"

class SrvClientReceiverThread: public Thread {

    uint16_t client_id;
    Socket &skt;
    Queue_2 &receiversQueue;
    std::atomic<bool> running;

    MessageToServer receive_msg();

    public:
        SrvClientReceiverThread(uint16_t client_id, Socket &skt, Queue_2 &receiversQueue);


        virtual void run() override;


};


#endif
