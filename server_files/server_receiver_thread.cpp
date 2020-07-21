
#include "server_receiver_thread.h"

SrvClientReceiverThread::SrvClientReceiverThread(
    uint16_t client_id, 
    Socket &skt, 
    MessageToServerQueue &receiversQueue) : client_id(client_id),
                             skt(skt),
                             receiversQueue(receiversQueue),
                             running(true) {}




void SrvClientReceiverThread::run() {

    while (running) {
        try {
            MessageToServer msg = this->receive_msg();
            if (msg.event_id == PROTOCOL_LOG_OFF)
                running = false;
            this->receiversQueue.push(msg);
        } catch (ReceiverThreadException& e) {
            this->running = false;
        }
    }
}



MessageToServer SrvClientReceiverThread::receive_msg() {
    MessageToServer msg;
    msgpack::unpacker pac;
    skt >> pac;
    if (pac.message_size() == 0)
        throw ReceiverThreadException();

    msgpack::object_handle oh;
    pac.next(oh);
    msgpack::object obj = oh.get();
    obj.convert(msg);
    return std::move(msg);
}


SrvClientReceiverThread::~SrvClientReceiverThread() {}

