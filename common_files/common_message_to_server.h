

#include <msgpack.hpp>
#include <vector>
#include <stdint.h>


struct MessageToServer {

    int16_t event_id;
    uint16_t player_id;
    std::vector<int16_t> args;


    MessageToServer();
    MessageToServer(int16_t event_id, uint16_t player_id, std::vector<int16_t> &args);

    MessageToServer(MessageToServer&& other);
    MessageToServer& operator=(MessageToServer&& other);

    MessageToServer(const MessageToServer&) = delete;
    MessageToServer& operator=(const MessageToServer&) = delete;

    MSGPACK_DEFINE(event_id, player_id, args)

};


