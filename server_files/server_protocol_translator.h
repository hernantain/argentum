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
#include "server_life_potion.h"
#include "server_mana_potion.h"
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
    void stop_moving(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para moverse a la derecha
    void move_right_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para moverse a la izquierda
    void move_left_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para moverse hacia arriba
    void move_top_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para moverse hacia abajo
    void move_down_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para depositar oro en el banco
    void deposit_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para retirar oro del banco
    void withdraw_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para resucitar un personaje
    void resurrect_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para tomar un item del suelo
    void take_item_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para dejar un item en el suelo
    void drop_item_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para equiparse una pocion
    void equip_potion_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para equiparse un escudo
    void equip_shield_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para equiparse un arma
    void equip_weapon_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para equiparse un casco
    void equip_helmet_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para equiparse una armadura
    void equip_armor_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para crear un NPC
    void create_npc_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para actualizar los NPCs
    void update_npcs_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para actualizar los Personajes
    void update_characters_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para crear un personaje
    void create_character(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para atacar a un atacable
    void attack_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para meditar
    void meditation_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para crear un Personaje
    void create_character_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);

    // Evento para desconectar un Personaje
    void log_off_event(MessageToServer &msg, ProtocolMessage &clientMessage, ServerWorld &world);

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
    void translate(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world);
};

#endif //_PROTOCOL_TRANSLATOR
