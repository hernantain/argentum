
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "server.h"
#include "server_os_error.h"

#define CONFIG_FILE 1
#define PARAMS 2
#define SUCCESS 0
#define ERROR 1
#define ARGS_ERROR_MSG "Argumentos inválidos. Uso: ./server <config.json>"

int main(int argc, char* argv[]) {
    try {
        srand (time(NULL));
        if (argc != PARAMS) {
            throw OSError(ARGS_ERROR_MSG);
        }
        Server srv(argv[CONFIG_FILE]);
        srv.run();

        return SUCCESS;
    } catch (const std::exception(&e)) {
        return ERROR;
    } catch (...) {
        return ERROR;
    }
}
