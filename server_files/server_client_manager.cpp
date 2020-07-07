
#include "server_client_manager.h"


ClientManager::ClientManager() {}


void ClientManager::add_client(uint16_t client_id, Socket &skt, Queue &receiversQueue) {
    std::unique_lock<std::mutex> lock(this->m);
    SrvClient* client = new SrvClient(client_id, skt, receiversQueue);
    this->clients.push_back(client);
}



void ClientManager::broadcastMessage(ProtocolMessage &updated_msg) {
    std::unique_lock<std::mutex> lock(this->m);
    for (unsigned int i = 0; i < clients.size(); ++i) { 
        this->clients[i]->send_message(updated_msg);
    }
}

