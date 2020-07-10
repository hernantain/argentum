
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
        if (msg.id_message == 67) {
            running = false;
            std::cout << "LLEGO LOG OFF" << std::endl;
        }
            
        this->receiversQueue.push(msg);
    }

    std::cout << "CERRANDO RECEIVERS QUEUE" << std::endl; 
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


