
#include <iostream>
#include <fstream>
#include <msgpack.hpp>

#include "server.h"
#include "server_os_error.h"

#include "server_elf.h"
#include "server_cleric.h"


#include "server_acceptor_thread.h"


#define FILE_ERROR_MSG "No se pudo abrir el archivo de configuración"

Server::Server(const char* config_file) : running(true) {
    this->initialize_config(config_file);
    const char* port = config["service"].asCString();
    this->skt.bind_and_listen(port);
}

void Server::run() {
    

    Thread* acceptor = new AcceptorThread(this->skt, this->config);
    acceptor->start();

    while (true) {
        
    }

    /**
     * 
     * LOGICA PARA CERRAR SERVEr
     */

}


void Server::initialize_config(const char* config_file) {
    std::ifstream file(config_file);
	if (!file.is_open()) throw OSError(FILE_ERROR_MSG);
    Json::Reader reader;
    reader.parse(file, config);
    file.close();
}



// ProtocolMessage Server::receive_msg(Socket skt) {
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
