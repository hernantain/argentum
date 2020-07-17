#ifndef _SENDER_THREAD
#define _SENDER_THREAD

#include <atomic>

#include "../common_files/common_sockets.h"
#include "../common_files/common_thread.h"
#include "../common_files/common_queue.h"
#include "../common_files/common_message_to_server.h"


class SenderThread : public Thread {

    Socket &skt;
    Queue_2 &queue;
    std::atomic<bool> running;

    public:
        SenderThread(Socket &skt, Queue_2 &queue);

        virtual void run() override;




};




#endif
