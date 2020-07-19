#ifndef _QUEUE
#define _QUEUE

#include <iostream>
#include <queue> 
#include <mutex>
#include <condition_variable>

#include "common_protocol_message.h"
#include "common_message_to_server.h"

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



class MessageToServerQueue {
    std::mutex m;
	std::condition_variable cond_var;
    std::queue<MessageToServer> messages;
    bool operating;

    public:
        MessageToServerQueue();

        void push(MessageToServer &message);

        MessageToServer pop();

        void stop();

        ~MessageToServerQueue();
};




#endif
