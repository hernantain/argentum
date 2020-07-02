

#include <iostream>
#include "server_client.h"



SrvClient::SrvClient(
    uint16_t client_id, 
    Socket skt, 
    Queue &receiversQueue,
    MapInfo &mapInfo) : client_id(client_id), 
                        skt(skt),
                        receiversQueue(receiversQueue),
                        mapInfo(mapInfo) {

    cReceiverThread = new SrvClientReceiverThread(client_id, skt, receiversQueue);
    cReceiverThread->start();

    cSenderThread = new SrvClientSenderThread(client_id, skt, messageQueue, mapInfo);
    cSenderThread->start();
    
    std::cout << "client ID EN CLIENT CREATION ES: " << client_id << std::endl;

}


void SrvClient::send_message(ProtocolMessage &updated_msg) {
    this->messageQueue.push(updated_msg);
}
