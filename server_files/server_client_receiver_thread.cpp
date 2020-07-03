
#include "server_client_receiver_thread.h"

#include <iostream>


SrvClientReceiverThread::SrvClientReceiverThread(
    uint16_t client_id, 
    Socket &skt, 
    Queue &receiversQueue) : client_id(client_id),
                             skt(skt),
                             receiversQueue(receiversQueue),
                             running(true) {}




void SrvClientReceiverThread::run() {

    std::cout << "SOCKET FD: " << skt.fd << std::endl;
    std::cout << "RECEIVER RUNNING" << std::endl;
    while (running) {
        ProtocolMessage msg = this->receive_msg();
        std::cout << "MESSAGE ID: " << msg.id_message << std::endl;
        std::cout << "PLAYER ID: " << msg.id_player << std::endl;
        this->receiversQueue.push(msg);
    }
}



ProtocolMessage SrvClientReceiverThread::receive_msg() {
    std::cout << "Corriendo" << std::endl;
    ProtocolMessage msg;
    msgpack::unpacker pac;
    skt >> pac;
    msgpack::object_handle oh;
    pac.next(oh);
    msgpack::object obj = oh.get();
    obj.convert(msg);
    return std::move(msg);
}


// void SrvClientReceiverThread::receiveFirstMessage() {
//     std::cout << "Corriendo" << std::endl;
//     ProtocolMessage msg;
//     msgpack::unpacker pac;
//     skt >> pac;
//     msgpack::object_handle oh;
//     pac.next(oh);
//     msgpack::object obj = oh.get();
//     obj.convert(msg);
//     return msg;

// }





