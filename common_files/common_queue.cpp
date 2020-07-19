#include <iostream>
#include <queue> 
#include <mutex>
#include <condition_variable>

#include "common_queue.h"
#include "common_queue_exception.h"

Queue::Queue() : operating(true) {} 


void Queue::push(ProtocolMessage &message) {
    std::unique_lock<std::mutex> lock(this->m);
	this->messages.push(std::move(message));
    this->cond_var.notify_all();
}

ProtocolMessage Queue::pop() {
    std::unique_lock<std::mutex> lock(this->m);

    while (this->messages.empty()) {
        if (!operating) 
            throw QueueNotOperatingException();
             
        this->cond_var.wait(lock);
    }

    ProtocolMessage msg = std::move(this->messages.front());
    this->messages.pop();
    return std::move(msg);
}

void Queue::stop() {
    std::unique_lock<std::mutex> lock(this->m);
    this->operating = false;
    this->cond_var.notify_all();
}

Queue::~Queue() {}




//////////////////////////////




MessageToServerQueue::MessageToServerQueue() : operating(true) {} 


void MessageToServerQueue::push(MessageToServer &message) {
    std::unique_lock<std::mutex> lock(this->m);
	this->messages.push(std::move(message));
    this->cond_var.notify_all();
}

MessageToServer MessageToServerQueue::pop() {
    std::unique_lock<std::mutex> lock(this->m);

    while (this->messages.empty()) {
        if (!operating) 
            throw QueueNotOperatingException();
             
        this->cond_var.wait(lock);
    }

    MessageToServer msg = std::move(this->messages.front());
    this->messages.pop();
    return std::move(msg);
}

void MessageToServerQueue::stop() {
    std::unique_lock<std::mutex> lock(this->m);
    this->operating = false;
    this->cond_var.notify_all();
}

MessageToServerQueue::~MessageToServerQueue() {}









