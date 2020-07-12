

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
        
    // std::cout << "EMPEZANDO EL BROADCAST" << std::endl;
    // for (unsigned int i = 0; i < updated_msg.characters.size(); ++i) {
    //     std::cout << std::endl;
    //     std::cout << "ENVIANDO --> PROT CHARACTER ID " << (int) updated_msg.characters[i].id << std::endl;
    //     std::cout << "ENVIANDO --> PROT CHARACTER ID RACE " << (int) updated_msg.characters[i].id_race << std::endl;
    //     std::cout << "ENVIANDO --> PROT CHARACTER ID CLASE " << (int) updated_msg.characters[i].id_class << std::endl;
    //     std::cout << "ENVIANDO --> PROT CHARACTER bodyposX " << updated_msg.characters[i].bodyPosX << std::endl;
    //     std::cout << "ENVIANDO --> PROT CHARACTER bodyposY " << updated_msg.characters[i].bodyPosY << std::endl;
    //     std::cout << "ENVIANDO --> PROT CHARACTER ORIENTAT " << (int) updated_msg.characters[i].orientation << std::endl;
    //     std::cout << "ENVIANDO --> PROT CHARACTER MANA " << updated_msg.characters[i].mana << std::endl;
    //     std::cout << "ENVIANDO --> PROT CHARACTER MAX_MANA " << updated_msg.characters[i].max_mana << std::endl;
    //     std::cout << "ENVIANDO --> PROT CHARACTER LIFE " << updated_msg.characters[i].life << std::endl;
    //     std::cout << "ENVIANDO --> PROT CHARACTER MAX_LIFE " << updated_msg.characters[i].max_life << std::endl;
    //     std::cout << "ENVIANDO --> PROT CHARACTER EXPERIEN " <<  updated_msg.characters[i].experience << std::endl;
    //     std::cout << "ENVIANDO --> PROT CHARACTER MAX EXP " << updated_msg.characters[i].max_experience << std::endl;
    //     std::cout << "ENVIANDO --> PROT CHARACTER ALIVE " << (int) updated_msg.characters[i].alive << std::endl;
    //     std::cout << std::endl;
    // }    
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

