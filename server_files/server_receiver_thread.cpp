
#include "server_receiver_thread.h"

#include <iostream>


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
            if (msg.event_id == PROTOCOL_LOG_OFF) {
                running = false;
                std::cout << "LLEGO LOG OFF" << std::endl;
            }
            this->receiversQueue.push(msg);
        } catch (ReceiverThreadException& e) {
            this->running = false;
            std::cout << "EXCEPCION EN EL RECEIVER THREAD !" << std::endl;
        }
    }

    std::cout << "CERRANDO RECEIVERS QUEUE" << std::endl; 
}



MessageToServer SrvClientReceiverThread::receive_msg() {
    // std::cout << "Recibiendo Mensaje" << std::endl;
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


SrvClientReceiverThread::~SrvClientReceiverThread() {
    std::cout << "DESTRUCTOR RECEIVER THREAD" << std::endl;
}

