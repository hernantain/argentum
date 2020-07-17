#include <msgpack.hpp>
#include <jsoncpp/json/json.h>

#include "../common_files/common_protocol_message.h"
#include "../common_files/common_collision_info.h"
#include "../common_files/common_protocol_codes.h"
#include "../common_files/common_message_to_server.h"

#include "server_world.h"
#include "server_attackable.h"
#include "server_character.h"
#include "server_npc.h"
#include "server_item.h"
#include "server_helmet.h"
#include "server_armor.h"
#include "server_character_factory.h"
#include "server_npc_factory.h"
#include "server_helmet_factory.h"
#include "server_armor_factory.h"
#include "server_weapon_factory.h"
#include "server_shield_factory.h"
#include "server_item_factory.h"

#ifndef _PROTOCOL_TRANSLATOR
#define _PROTOCOL_TRANSLATOR

/* 
 * Clase que se encarga de traducir los codigos de los eventos recibidos 
 * y mapearlos a una funcionalidad del modelo
 */
class ProtocolTranslator {
private:
    Json::Value &config;
    CollisionInfo &collisionInfo;

    // Evento parar de moverse 
    ProtocolMessage stop_moving(MessageToServer& msg, ServerWorld &world);

    // Evento para moverse a la derecha
    ProtocolMessage move_right_event(MessageToServer& msg, ServerWorld &world);

    // Evento para moverse a la izquierda
    ProtocolMessage move_left_event(MessageToServer& msg, ServerWorld &world);

    // Evento para moverse hacia arriba
    ProtocolMessage move_top_event(MessageToServer& msg, ServerWorld &world);

    // Evento para moverse hacia abajo
    ProtocolMessage move_down_event(MessageToServer& msg, ServerWorld &world);

    // Evento para depositar oro en el banco
    ProtocolMessage deposit_event(MessageToServer& msg, ServerWorld &world);

    // Evento para retirar oro del banco
    ProtocolMessage withdraw_event(MessageToServer& msg, ServerWorld &world);

    // Evento para resucitar un personaje
    ProtocolMessage resurrect_event(MessageToServer& msg, ServerWorld &world);

    // Evento para tomar un item del suelo
    ProtocolMessage take_item_event(MessageToServer& msg, ServerWorld &world);

    // Evento para dejar un item en el suelo
    ProtocolMessage drop_item_event(MessageToServer& msg, ServerWorld &world);

    // Evento para equiparse un escudo
    ProtocolMessage equip_shield_event(MessageToServer& msg, ServerWorld &world);

    // Evento para equiparse un arma
    ProtocolMessage equip_weapon_event(MessageToServer& msg, ServerWorld &world);

    // Evento para equiparse un casco
    ProtocolMessage equip_helmet_event(MessageToServer& msg, ServerWorld &world);

    // Evento para equiparse una armadura
    ProtocolMessage equip_armor_event(MessageToServer& msg, ServerWorld &world);

    // Evento para crear un NPC
    ProtocolMessage create_npc_event(MessageToServer& msg, ServerWorld &world);

    // Evento para actualizar los NPCs
    ProtocolMessage update_npcs_event(MessageToServer& msg, ServerWorld &world);

    // Evento para actualizar los Personajes
    ProtocolMessage update_characters_event(MessageToServer& msg, ServerWorld &world);

    // Evento para crear un personaje
    ProtocolMessage create_character(MessageToServer& msg, ServerWorld &world);

    // Evento para atacar a un atacable
    ProtocolMessage attack_event(MessageToServer& msg, ServerWorld &world);

    // Evento para meditar
    ProtocolMessage meditation_event(MessageToServer& msg, ServerWorld &world);

    // Evento para crear un Personaje
    ProtocolMessage create_character_event(MessageToServer& msg, ServerWorld &world);

    // Evento para desconectar un Personaje
    ProtocolMessage log_off_event(MessageToServer&msg, ServerWorld &world);

    // Evento actualizar todos los personajes del mundo
    void get_all_characters(ProtocolMessage& msg, ServerWorld &world);

    // Evento actualizar todos los NPCs del mundo
    void get_all_npcs(ProtocolMessage& msg, ServerWorld &world);

    // Evento actualizar todos los Items del mundo
    void get_all_items(ProtocolMessage& msg, ServerWorld &world);

    // Evento actualizar todos los NPCs, Items y Personajes del mundo
    void get_world(ProtocolMessage& msg, ServerWorld &world);

public:
    ProtocolTranslator(Json::Value &config, CollisionInfo &collisionInfo);

    // Mapea el codigo recibido en un mensaje del protocolo
    ProtocolMessage translate(MessageToServer& msg, ServerWorld &world);
};

#endif //_PROTOCOL_TRANSLATOR
