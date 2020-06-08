#ifndef _SENDER_THREAD
#define _SENDER_THREAD

#include "common_sockets.h"
#include "common_thread.h"
#include "common_queue.h"

class SenderThread : public Thread {

    Socket &skt;
    Queue &queue;


    public:
        SenderThread(Socket &skt, Queue &queue);

        virtual void run() override;




};




#endif
