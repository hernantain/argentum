
#include "../common_mapinfo.h"
#include "server_processor_thread.h"

#include <iostream>

ServerProcessorThread::ServerProcessorThread(
    Queue &receiversQueue,
    std::vector<SrvClient*> &clients,
    CollisionInfo &collisionInfo,
    Json::Value &config) : receiversQueue(receiversQueue),
                            clients(clients),
                            collisionInfo(collisionInfo),
                            config(config),
                            running(true) {}




void ServerProcessorThread::run() {

    std::cout << "PROCESSOR CORRIENDO" << std::endl;
    ProtocolTranslator protocol_translator(config, collisionInfo);
    ServerWorld serverWorld;
    while (running) {

        std::cout << "ACA ANTES" << std::endl;
        ProtocolMessage received_msg = this->receiversQueue.pop();
        std::cout << "ACA DESPUES" << std::endl;
        ProtocolMessage updated_msg = protocol_translator.translate(received_msg, serverWorld);

        this->broadcastMessage(updated_msg);

    }
}



void ServerProcessorThread::broadcastMessage(ProtocolMessage &updated_msg) {
    for (unsigned int i = 0; i < clients.size(); ++i) {
        this->clients[i]->send_message(updated_msg);
    }
}

