
#include "common_mapinfo.h"
#include "server_processor_thread.h"


ServerProcessorThread::ServerProcessorThread(
    Queue &receiversQueue,
    std::vector<SrvClient> &clients,
    CollisionInfo &collisionInfo,
    Json::Value &config) : receiversQueue(receiversQueue),
                            clients(clients),
                            collisionInfo(collisionInfo),
                            config(config),
                            running(true) {}




void ServerProcessorThread::run() {

    ProtocolTranslator protocol_translator(config, collisionInfo);
    ServerWorld serverWorld;
    while (running) {

        ProtocolMessage received_msg = this->receiversQueue.pop();
        ProtocolMessage updated_msg = protocol_translator.translate(received_msg, serverWorld);

        // this->broadcastMessage

    }



}