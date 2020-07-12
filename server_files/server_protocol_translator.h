#include <msgpack.hpp>
#include <jsoncpp/json/json.h>

#include "../common_files/common_protocol_message.h"
#include "../common_files/common_collision_info.h"
#include "../common_files/common_protocol_codes.h"

#include "server_world.h"
#include "server_attackable.h"
#include "server_character.h"
#include "server_npc.h"
#include "server_helmet.h"
#include "server_armor.h"
#include "server_character_factory.h"
#include "server_npc_factory.h"
#include "server_helmet_factory.h"
#include "server_armor_factory.h"
#include "server_weapon_factory.h"
#include "server_shield_factory.h"

#ifndef _PROTOCOL_TRANSLATOR
#define _PROTOCOL_TRANSLATOR

/* 
 * Clase que se encarga de ejecutar los codigos recibidos y matchearlos a una
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
    void deposit_event(ProtocolMessage& msg, ServerWorld &world);
    void take_item_event(ProtocolMessage& msg, ServerWorld &world);
    void equip_shield_event(ProtocolMessage& msg, ServerWorld &world);
    void equip_weapon_event(ProtocolMessage& msg, ServerWorld &world);
    void equip_helmet_event(ProtocolMessage& msg, ServerWorld &world);
    void equip_armor_event(ProtocolMessage& msg, ServerWorld &world);
    void create_npc_event(ProtocolMessage& msg, ServerWorld &world);
    void update_npcs_event(ProtocolMessage& msg, ServerWorld &world);
    void update_characters_event(ProtocolMessage& msg, ServerWorld &world);
    void create_character(ProtocolMessage& msg, ServerWorld &world);
    void attack_event(ProtocolMessage& msg, ServerWorld &world);
    void meditation_event(ProtocolMessage& msg, ServerWorld &world);
    void create_character_event(ProtocolMessage& msg, ServerWorld &world);
    void log_off_event(ProtocolMessage&msg, ServerWorld &world);
    void get_all_characters(ProtocolMessage& msg, ServerWorld &world);
    void get_all_npcs(ProtocolMessage& msg, ServerWorld &world);
    void get_all_items(ProtocolMessage& msg, ServerWorld &world);
    void get_world(ProtocolMessage& msg, ServerWorld &world);

public:
    ProtocolTranslator(Json::Value &config, CollisionInfo &collisionInfo);

    // Transforma el codigo recibido un mensaje del protocolo
    void translate(ProtocolMessage& msg, ServerWorld &world);
};

#endif //_PROTOCOL_TRANSLATOR
