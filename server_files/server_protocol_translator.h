#include <msgpack.hpp>
#include <jsoncpp/json/json.h>

#include "../common_protocol_message.h"
#include "../common_collision_info.h"

#include "server_world.h"
#include "server_character.h"
#include "server_helmet.h"
#include "server_armor.h"
#include "server_character_factory.h"
#include "server_helmet_factory.h"
#include "server_armor_factory.h"
#include "server_weapon_factory.h"

#ifndef _PROTOCOL_TRANSLATOR
#define _PROTOCOL_TRANSLATOR

// Received from the client
#define PROTOCOL_MOVE_STOP 9
#define PROTOCOL_MOVE_TOP 10
#define PROTOCOL_MOVE_RIGHT 11
#define PROTOCOL_MOVE_LEFT 12
#define PROTOCOL_MOVE_DOWN 13

#define PROTOCOL_ATTACK 2
#define PROTOCOL_EQUIP_HELMET 3
#define PROTOCOL_EQUIP_ARMOR 4
#define PROTOCOL_EQUIP_WEAPON 5
#define PROTOCOL_EQUIP_SHIELD 6

#define PROTOCOL_CREATE_CHARACTER 65
#define PROTOCOL_CREATE_CHARACTER_CONFIRM 66

#define PROTOCOL_CREATE_NPC 70
#define PROTOCOL_CREATE_NPC 71

// Sending to the client
#define PROTOCOL_MOVE_CONFIRM 20
#define PROTOCOL_HELMET_CONFIRM 30
#define PROTOCOL_ARMOR_CONFIRM 31
#define PROTOCOL_WEAPON_CONFIRM 32
#define PROTOCOL_SHIELD_CONFIRM 33

/* Clase que se encarga de ejecutar los codigos recibidos y matchearlos a una
 * función del personaje.
 */
class ProtocolTranslator {
private:
    Json::Value &config;
    CollisionInfo &collisionInfo;

    void stop_moving(ProtocolMessage& msg, ServerWorld &world);
    void move_right_event(ProtocolMessage& msg, ServerWorld &world);
    void move_left_event(ProtocolMessage& msg, ServerWorld &world);
    void move_top_event(ProtocolMessage& msg, ServerWorld &world);
    void move_down_event(ProtocolMessage& msg, ServerWorld &world);
    void equip_shield_event(ProtocolMessage& msg, ServerWorld &world);
    void equip_weapon_event(ProtocolMessage& msg, ServerWorld &world);
    void equip_helmet_event(ProtocolMessage& msg, ServerWorld &world);
    void equip_armor_event(ProtocolMessage& msg, ServerWorld &world);
    void create_npc(ProtocolMessage& msg, ServerWorld &world);
    void create_character(ProtocolMessage& msg, ServerWorld &world);
    void get_all_characters(ProtocolMessage& msg, ServerWorld &world);

public:
    ProtocolTranslator(Json::Value &config, CollisionInfo &collisionInfo);

    // Transforma el codigo recibido un mensaje del protocolo
    void translate(ProtocolMessage& msg, ServerWorld &world);
};

#endif //_PROTOCOL_TRANSLATOR
