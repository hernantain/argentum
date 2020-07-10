

#include <iostream>
#include "server_client.h"



SrvClient::SrvClient(
    uint16_t client_id, 
    Socket skt, 
    Queue &receiversQueue) : client_id(client_id), 
                            skt(skt),
                            receiversQueue(receiversQueue),
                            active(true) {

    cReceiverThread = new SrvClientReceiverThread(client_id, this->skt, receiversQueue);
    cReceiverThread->start();

    cSenderThread = new SrvClientSenderThread(client_id, this->skt, messageQueue);
    cSenderThread->start();
}


void SrvClient::send_message(ProtocolMessage &updated_msg) {
    if (updated_msg.id_message == 68 && updated_msg.id_player == this->client_id)
        this->active = false;
        
    this->messageQueue.push(updated_msg);
}


bool SrvClient::is_active() {
    return this->active;
}


SrvClient::~SrvClient() {
    this->cReceiverThread->join();
    delete this->cReceiverThread;

    this->cSenderThread->join();
    delete this->cSenderThread;
}

