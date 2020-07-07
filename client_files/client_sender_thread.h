#ifndef _SENDER_THREAD
#define _SENDER_THREAD

#include <atomic>

#include "../common_files/common_sockets.h"
#include "../common_files/common_thread.h"
#include "../common_files/common_queue.h"

class SenderThread : public Thread {

    Socket &skt;
    Queue &queue;
    std::atomic<bool> running;

    public:
        SenderThread(Socket &skt, Queue &queue);

        virtual void run() override;




};




#endif
