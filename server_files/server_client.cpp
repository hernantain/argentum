


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

}