#include <stdint.h>
#include <iostream>

#include "server_world.h"
#include "server_protocol_translator.h"

#include "server_elf.h"
#include "server_cleric.h"

ProtocolTranslator::ProtocolTranslator(
    Json::Value &config, 
    CollisionInfo &collisionInfo) : config(config),
                                    collisionInfo(collisionInfo) {}


void ProtocolTranslator::translate(ProtocolMessage& msg, ServerWorld& world) {
    int code = msg.id_message;
    switch (code) {
        case 65: return create_character(msg, world);
        case PROTOCOL_MOVE_RIGHT: return move_right_event(msg, world);
        case PROTOCOL_MOVE_LEFT: return move_left_event(msg, world);
        case PROTOCOL_MOVE_TOP: return move_top_event(msg, world);
        case PROTOCOL_MOVE_DOWN: return move_down_event(msg, world);
        case PROTOCOL_EQUIP_HELMET: return equip_helmet_event(msg, world);
        case PROTOCOL_EQUIP_ARMOR: return equip_armor_event(msg, world);
    }
}

void ProtocolTranslator::equip_armor_event(ProtocolMessage &msg, ServerWorld &world) {

    int armor_id = msg.characters[0].armorId;
    ArmorFactory factory;
    Armor armor = factory.make_armor(armor_id, config);
    world.characters[msg.id_player]->equip_armor(armor);
    msg.id_message = PROTOCOL_ARMOR_CONFIRM;
}


void ProtocolTranslator::equip_helmet_event(ProtocolMessage &msg, ServerWorld &world) {
    int helmet_id = msg.characters[0].helmetId;
    HelmetFactory factory;
    Helmet helmet = factory.make_helmet(helmet_id, config);
    world.characters[msg.id_player]->equip_helmet(helmet);
    msg.id_message = PROTOCOL_HELMET_CONFIRM;
}


void ProtocolTranslator::move_right_event(ProtocolMessage &msg, ServerWorld &world) {

    world.characters[msg.id_player]->move_right();
    this->get_all_characters(msg, world);

    msg.id_message = PROTOCOL_MOVE_CONFIRM;
}


void ProtocolTranslator::move_left_event(ProtocolMessage &msg, ServerWorld &world) {

    world.characters[msg.id_player]->move_left();
    this->get_all_characters(msg, world);

    msg.id_message = PROTOCOL_MOVE_CONFIRM;
}


void ProtocolTranslator::move_top_event(ProtocolMessage &msg, ServerWorld &world) {

    world.characters[msg.id_player]->move_top();
    this->get_all_characters(msg, world);

    msg.id_message = PROTOCOL_MOVE_CONFIRM;
}


void ProtocolTranslator::move_down_event(ProtocolMessage &msg, ServerWorld &world) {

    world.characters[msg.id_player]->move_down();
    this->get_all_characters(msg, world);
    msg.id_message = PROTOCOL_MOVE_CONFIRM;
}



void ProtocolTranslator::create_character(ProtocolMessage& msg, ServerWorld &world) {
    
    Elf race(config);
    Cleric c(config);       /* LOGICA PARA MANEJAR LAS RAZAS Y CLASES ACA */
    Character* character = new Character(msg.id_player, config, c, race, collisionInfo);
    world.add(msg.id_player, character);

    msg.id_message = 66;
    this->get_all_characters(msg, world);
}


void ProtocolTranslator::get_all_characters(ProtocolMessage& msg, ServerWorld &world) {
    std::map<int16_t, Character*>::iterator itr;
    std::vector<ProtocolCharacter> tmp;

    for (itr = world.characters.begin(); itr != world.characters.end(); ++itr) { 
        ProtocolCharacter protocolCharacter;
        itr->second->populate_protocol_character(protocolCharacter);
        tmp.push_back(std::move(protocolCharacter));
        msg.characters = std::move(tmp);
    }
}
