#include <msgpack.hpp>
#include "../common_protocol_message.h"
#include "server_character.h"

#ifndef _PROTOCOL_TRANSLATOR
#define _PROTOCOL_TRANSLATOR

// Received from the client
#define PROTOCOL_MOVE 1
#define PROTOCOL_ATTACK 2

// Sending to the client
#define PROTOCOL_MOVE_CONFIRM 20

/* Clase que se encarga de ejecutar los codigos recibidos y matchearlos a una
 * función del personaje.
 */
class ProtocolTranslator {
private:
    ProtocolMessage move_event(ProtocolMessage& msg, Character& character);

public:
    ProtocolTranslator();

    // Transforma el codigo recibido un mensaje del protocolo
    ProtocolMessage translate(ProtocolMessage& msg, Character& character);
};

#endif //_PROTOCOL_TRANSLATOR
