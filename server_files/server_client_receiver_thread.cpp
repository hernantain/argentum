
#include "server_client_receiver_thread.h"




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







