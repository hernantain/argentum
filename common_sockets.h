#ifndef COMMON_SOCKETS
#define COMMON_SOCKETS

#include <stdint.h>
#include <string>
#include <msgpack.hpp>

/**
 * Clase Socket: Encapsula la logica de los sockets, como el TDA del TP1.
 * Posee los metodos necesarios para conectarse si es un cliente o para hacer 
 * un bind y un accept en el caso de Server; ademas de los otros metodos 
 * como close, shutdown, send y recv.
 * 
 * El accept devuelve un nuevo Socket usando move semantics.
 * 
 * Tiene sobrecargados los operadores '()' y '>>'.
 * 
 * operator(): para hacer el envio de mensajes de distinto tipo 
 *              usando la notacion skt(MESSAGE).
 * 
 * operator>>: para hacer la recepcion de mensajes de distinto tipo
 *              usando la notacion skt >> var.
 * 
 * Los tipos para ambos operadores son: uint8, uint16, uint32 y string.
 */
class Socket {
    explicit Socket(int fd);

    public:
        int fd;
        Socket();

        void connect_to(const char *host, const char *port);

        void turnoff_channel(int mode);

        void bind_and_listen(const char *port);

        void send_message(char *buf, int size) const;

        void receive(char *buf, int size) const;

        Socket accept_client();

        void close_socket();
    
        void operator()(uint8_t &com) const;
        void operator()(uint16_t &number) const;
        void operator()(uint32_t &len) const;
        void operator()(const std::string &message) const;
        void operator()(msgpack::sbuffer &sbuf) const;

        void operator>>(uint8_t &com) const;
        void operator>>(uint16_t &buf) const;
        void operator>>(uint32_t &len) const;
        void operator>>(std::string &message) const;
        void operator>>(msgpack::unpacker &pack) const;
};



#endif
