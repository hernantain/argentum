#include <iostream>
#include <queue> 
#include <mutex>
#include <condition_variable>

#include "common_queue.h"
#include "common_queue_exception.h"

Queue::Queue() : operating(true) {} 


void Queue::push(const ProtocolMessage &message) {
    std::cout << "PASA POR ACA" << std::endl;
    std::unique_lock<std::mutex> lock(this->m);
	this->messages.push(message);
    this->cond_var.notify_all();
}

ProtocolMessage Queue::pop() {
    std::unique_lock<std::mutex> lock(this->m);

    while (this->messages.empty()) {
        if (!operating) 
            throw QueueNotOperatingException();
             
        this->cond_var.wait(lock);
    }

    ProtocolMessage msg = this->messages.front();
    this->messages.pop();
    return msg;
}

void Queue::stop() {
    std::unique_lock<std::mutex> lock(this->m);
    this->operating = false;
    this->cond_var.notify_all();
}

Queue::~Queue() {}
