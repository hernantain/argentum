
#include <iostream>
#include <fstream>

#include "server.h"
#include "server_os_error.h"

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

    char c;
    while (true) {
        std::cin >> c;
        if (c == 'q') break;
    }

    skt.close_socket();
    acceptor->join();
    delete acceptor;
}


void Server::initialize_config(const char* config_file) {
    std::ifstream file(config_file);
	if (!file.is_open()) throw OSError(FILE_ERROR_MSG);
    Json::Reader reader;
    reader.parse(file, config);
    file.close();
}

