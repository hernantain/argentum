#include <msgpack.hpp>
#include <jsoncpp/json/json.h>
#include "../common_protocol_message.h"
#include "server_character.h"
#include "server_helmet.h"
#include "server_helmet_factory.h"

#ifndef _PROTOCOL_TRANSLATOR
#define _PROTOCOL_TRANSLATOR

// Received from the client
#define PROTOCOL_MOVE 1
#define PROTOCOL_ATTACK 2
#define PROTOCOL_EQUIP_HELMET 3
#define PROTOCOL_EQUIP_ARMOR 4

// Sending to the client
#define PROTOCOL_MOVE_CONFIRM 20
#define PROTOCOL_EQUIP_CONFIRM 30

/* Clase que se encarga de ejecutar los codigos recibidos y matchearlos a una
 * función del personaje.
 */
class ProtocolTranslator {
private:
    Json::Value &config;

    ProtocolMessage move_event(ProtocolMessage& msg, Character& character);
    ProtocolMessage equip_helmet_event(ProtocolMessage& msg, Character& character);
public:
    ProtocolTranslator(Json::Value &config);

    // Transforma el codigo recibido un mensaje del protocolo
    ProtocolMessage translate(ProtocolMessage& msg, Character& character);
};

#endif //_PROTOCOL_TRANSLATOR
