#ifndef _QUEUE
#define _QUEUE

#include <iostream>
#include <queue> 
#include <mutex>
#include <condition_variable>

#include "common_protocol_message.h"


class Queue {
    std::mutex m;
	std::condition_variable cond_var;
    std::queue<ProtocolMessage> messages;
    bool operating;

    public:
        Queue();

        void push(ProtocolMessage &message);

        ProtocolMessage pop();

        void stop();

        ~Queue();
};

#endif
