#include <string>
#include "common_socket_protocol.h"

// SocketProtocol::SocketProtocol(const char *ip, const char *port) :
//     socket(ip, port) {}

SocketProtocol::SocketProtocol(Socket &&other_socket) : 
    socket(std::move(other_socket)) {}


void SocketProtocol::send_command(int command_id) {
}

void SocketProtocol::send_movement() {
    send_command(PROTOCOL_MOVEMENT);
}

void SocketProtocol::send_character_info(size_t id, double x, double y) {
    send_command(PROTOCOL_CHARACTER_INFO);
}

void SocketProtocol::send_stage_info(int width, int height, std::string background) {
    send_command(PROTOCOL_STAGE_INFO);
}

void SocketProtocol::send_closed_connection() {
  send_command(PROTOCOL_CLOSED_CON);
}

SocketProtocol::~SocketProtocol() {}
