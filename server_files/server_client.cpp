

#include <iostream>
#include "server_client.h"



SrvClient::SrvClient(
    uint16_t client_id, 
    Socket skt, 
    MessageToServerQueue &receiversQueue) : client_id(client_id), 
                                            skt(std::move(skt)),
                                            receiversQueue(receiversQueue),
                                            active(true) {

    cReceiverThread = new SrvClientReceiverThread(client_id, this->skt, receiversQueue);
    cReceiverThread->start();

    cSenderThread = new SrvClientSenderThread(client_id, this->skt, messageQueue);
    cSenderThread->start();
}


void SrvClient::send_message(ProtocolMessage &updated_msg) {
    if (updated_msg.id_message == PROTOCOL_LOG_OFF_CONFIRM && updated_msg.id_player == this->client_id)
        this->active = false;
    this->messageQueue.push(updated_msg);
}


bool SrvClient::is_active() const {
    return this->active;
}

void SrvClient::stop() {
    this->skt.turnoff_channel(SHUT_RD);
    messageQueue.stop();
    this->skt.close_socket();
}


SrvClient::~SrvClient() {
    this->cReceiverThread->join();
    delete this->cReceiverThread;

    this->cSenderThread->join();
    delete this->cSenderThread;
}

