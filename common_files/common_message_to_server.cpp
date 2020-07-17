

#include "common_message_to_server.h"


MessageToServer::MessageToServer(
    int16_t event_id, 
    uint16_t player_id, 
    std::vector<int16_t> &args) : event_id(event_id), player_id(player_id) {
    this->args = args;
}


MessageToServer::MessageToServer(MessageToServer&& other) {
    this->event_id = std::move(other.event_id);
    this->player_id = std::move(other.player_id);
    this->args = other.args;
}


MessageToServer& MessageToServer::operator=(MessageToServer&& other) {
    this->event_id = std::move(other.event_id);
    this->player_id = std::move(other.player_id);
    this->args = other.args;
    return *this;
}
