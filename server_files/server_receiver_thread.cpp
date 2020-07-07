
#include "server_receiver_thread.h"

#include <iostream>


SrvClientReceiverThread::SrvClientReceiverThread(
    uint16_t client_id, 
    Socket &skt, 
    Queue &receiversQueue) : client_id(client_id),
                             skt(skt),
                             receiversQueue(receiversQueue),
                             running(true) {}




void SrvClientReceiverThread::run() {

    while (running) {
        ProtocolMessage msg = this->receive_msg();
        this->receiversQueue.push(msg);
    }
}



ProtocolMessage SrvClientReceiverThread::receive_msg() {
    // std::cout << "Recibiendo Mensaje" << std::endl;
    ProtocolMessage msg;
    msgpack::unpacker pac;
    skt >> pac;
    msgpack::object_handle oh;
    pac.next(oh);
    msgpack::object obj = oh.get();
    obj.convert(msg);
    return std::move(msg);
}


