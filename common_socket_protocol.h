#ifndef COMMON_SOCKET_PROTOCOL
#define COMMON_SOCKET_PROTOCOL

#include "common_sockets.h"

// Send by client
#define PROTOCOL_MOVEMENT 1
#define PROTOCOL_CLOSED_CON 2

// Send by server
#define PROTOCOL_CHARACTER_INFO 40
#define PROTOCOL_STAGE_INFO 50

/* Clase protocolo que abstrae al sistema de como se realiza la
 * comunicación entre los clientes y el servidor.
 * Esta implementación particular utiliza un socket para la comunicación
 */
class SocketProtocol {
private:
    Socket socket;

    // No copiable
    SocketProtocol(const SocketProtocol &other) = delete;
    SocketProtocol& operator=(const SocketProtocol &other) = delete;

    void send_command(int command_id);
public:
    /* Constructor que se conecta a la ip y puerto indicados */
    SocketProtocol(const char* ip, const char* port);

    /* Constructor que utiliza el socket recibido para la comunicación */
    explicit SocketProtocol(Socket&& other_socket);

    SocketProtocol(SocketProtocol&& other) noexcept = default;

    /* Envía el cliente */
    void send_movement();

    /* Envía el servidor */
    void send_character_info(size_t id, double x, double y);
    void send_stage_info(int width, int height, std::string background);

    /* Envían ambos */
    void send_closed_connection();

    void shutdown(int mode);
    ~SocketProtocol();
};

#endif // COMMON_SOCKET_PROTOCOL
