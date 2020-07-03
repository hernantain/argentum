

#include <iostream>
#include "server_client.h"



SrvClient::SrvClient(
    uint16_t client_id, 
    Socket skt, 
    Queue &receiversQueue) : client_id(client_id), 
                        skt(skt),
                        receiversQueue(receiversQueue) {

    cReceiverThread = new SrvClientReceiverThread(client_id, this->skt, receiversQueue);
    cReceiverThread->start();

    cSenderThread = new SrvClientSenderThread(client_id, this->skt, messageQueue);
    cSenderThread->start();
}


void SrvClient::send_message(ProtocolMessage &updated_msg) {
    this->messageQueue.push(updated_msg);
}
