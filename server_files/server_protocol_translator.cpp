#include <stdint.h>
#include <iostream>

#include "server_world.h"
#include "server_protocol_translator.h"

ProtocolTranslator::ProtocolTranslator(
    Json::Value &config, 
    CollisionInfo &collisionInfo) : config(config),
                                    collisionInfo(collisionInfo) {}


void ProtocolTranslator::translate(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld& world) {
    int code = msg.event_id;
    // std::cout << "PROCESANDO: " << code << std::endl;
    switch (code) {
        case PROTOCOL_CREATE_CHARACTER: return create_character_event(msg, clientMessage, world);
        case PROTOCOL_CREATE_NPC: return create_npc_event(msg, clientMessage, world);
        case PROTOCOL_UPDATE_NPCS: return update_npcs_event(msg, clientMessage, world);
        case PROTOCOL_UPDATE_CHARACTERS: return update_characters_event(msg, clientMessage, world);
        case PROTOCOL_MOVE_RIGHT: return move_right_event(msg, clientMessage, world);
        case PROTOCOL_MOVE_LEFT: return move_left_event(msg, clientMessage, world);
        case PROTOCOL_MOVE_TOP: return move_top_event(msg, clientMessage, world);
        case PROTOCOL_MOVE_DOWN: return move_down_event(msg, clientMessage, world);
        case PROTOCOL_RESURRECT: return resurrect_event(msg, clientMessage, world);
        case PROTOCOL_DEPOSIT: return deposit_event(msg, clientMessage, world);
        case PROTOCOL_WITHDRAW: return withdraw_event(msg, clientMessage, world);
        case PROTOCOL_EQUIP_HELMET: return equip_helmet_event(msg, clientMessage, world);
        case PROTOCOL_EQUIP_ARMOR: return equip_armor_event(msg, clientMessage, world);
        case PROTOCOL_EQUIP_WEAPON: return equip_weapon_event(msg, clientMessage, world);
        case PROTOCOL_EQUIP_SHIELD: return equip_shield_event(msg, clientMessage, world);
        case PROTOCOL_MOVE_STOP: return stop_moving(msg, clientMessage, world);
        case PROTOCOL_ATTACK: return attack_event(msg, clientMessage, world);
        case PROTOCOL_MEDITATION: return meditation_event(msg, clientMessage, world);
        case PROTOCOL_TAKE_ITEM: return take_item_event(msg, clientMessage, world);
        case PROTOCOL_DROP_ITEM: return drop_item_event(msg, clientMessage, world);
        case PROTOCOL_LOG_OFF: return log_off_event(msg, clientMessage, world);
    }
}

void ProtocolTranslator::equip_shield_event(MessageToServer &msg, ProtocolMessage &clientMessage, ServerWorld &world) {

    uint8_t shield_id = msg.args[0];
    Shield shield = ShieldFactory::make_shield(shield_id, config);
    world.characters[msg.player_id]->equip_shield(shield);
    
    clientMessage.id_message = PROTOCOL_SHIELD_CONFIRM;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}

void ProtocolTranslator::equip_weapon_event(MessageToServer &msg, ProtocolMessage &clientMessage, ServerWorld &world) {
    uint8_t weapon_id = msg.args[0];
    Weapon weapon = WeaponFactory::make_weapon(weapon_id, config);
    world.characters[msg.player_id]->equip_weapon(weapon);
    
    clientMessage.id_message = PROTOCOL_WEAPON_CONFIRM;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}

void ProtocolTranslator::equip_armor_event(MessageToServer &msg, ProtocolMessage &clientMessage, ServerWorld &world) {
    uint8_t armor_id = msg.args[0];
    Armor armor = ArmorFactory::make_armor(armor_id, config);
    world.characters[msg.player_id]->equip_armor(armor);

    clientMessage.id_message = PROTOCOL_ARMOR_CONFIRM;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}


void ProtocolTranslator::equip_helmet_event(MessageToServer &msg, ProtocolMessage &clientMessage, ServerWorld &world) {
    uint8_t helmet_id = msg.args[0];
    Helmet helmet = HelmetFactory::make_helmet(helmet_id, config);
    world.characters[msg.player_id]->equip_helmet(helmet);
    
    clientMessage.id_message = PROTOCOL_HELMET_CONFIRM;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}

void ProtocolTranslator::resurrect_event(MessageToServer &msg, ProtocolMessage &clientMessage, ServerWorld &world) {
    if (world.has_priest_close(msg.player_id))
        world.characters[msg.player_id]->resurrect();
    
    clientMessage.id_message = PROTOCOL_RESURRECT_CONFIRM;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}

void ProtocolTranslator::deposit_event(MessageToServer &msg, ProtocolMessage &clientMessage, ServerWorld &world) {
    if (world.has_banker_close(msg.player_id))
        world.characters[msg.player_id]->deposit_gold();
    
    clientMessage.id_message = PROTOCOL_DEPOSIT_CONFIRM;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}

void ProtocolTranslator::withdraw_event(MessageToServer &msg, ProtocolMessage &clientMessage, ServerWorld &world) {
    if (world.has_banker_close(msg.player_id))
        world.characters[msg.player_id]->withdraw_gold();

    clientMessage.id_message = PROTOCOL_WITHDRAW_CONFIRM;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}

void ProtocolTranslator::stop_moving(MessageToServer &msg, ProtocolMessage &clientMessage, ServerWorld &world) {

    world.characters[msg.player_id]->stop_moving();
    
    clientMessage.id_message = PROTOCOL_MOVE_CONFIRM;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}


void ProtocolTranslator::move_right_event(MessageToServer &msg, ProtocolMessage &clientMessage, ServerWorld &world) {
    
    world.move_character_right(msg.player_id);

    clientMessage.id_message = PROTOCOL_MOVE_CONFIRM;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}


void ProtocolTranslator::move_left_event(MessageToServer &msg, ProtocolMessage &clientMessage, ServerWorld &world) {

    world.move_character_left(msg.player_id);

    clientMessage.id_message = PROTOCOL_MOVE_CONFIRM;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}


void ProtocolTranslator::move_top_event(MessageToServer &msg, ProtocolMessage &clientMessage, ServerWorld &world) {

    world.move_character_top(msg.player_id);

    clientMessage.id_message = PROTOCOL_MOVE_CONFIRM;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}


void ProtocolTranslator::move_down_event(MessageToServer &msg, ProtocolMessage &clientMessage, ServerWorld &world) {

    world.move_character_down(msg.player_id);

    clientMessage.id_message = PROTOCOL_MOVE_CONFIRM;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}

void ProtocolTranslator::take_item_event(MessageToServer &msg, ProtocolMessage &clientMessage, ServerWorld &world) {
    
    world.player_take_item(msg.player_id);

    clientMessage.id_message = PROTOCOL_TAKE_ITEM_CONFIRM;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}

void ProtocolTranslator::drop_item_event(MessageToServer &msg, ProtocolMessage &clientMessage, ServerWorld &world) {
    uint8_t item_id = msg.args[0];
    world.characters[msg.player_id]->drop_item(item_id, world.items);

    clientMessage.id_message = PROTOCOL_DROP_ITEM_CONFIRM;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}

void ProtocolTranslator::meditation_event(MessageToServer &msg, ProtocolMessage &clientMessage, ServerWorld &world) {
    
    world.characters[msg.player_id]->meditate();

    clientMessage.id_message = PROTOCOL_MEDITATE_CONFIRM;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}

void ProtocolTranslator::attack_event(MessageToServer &msg, ProtocolMessage &clientMessage, ServerWorld &world) {
    int other_posX = msg.args[0];
    int other_posY = msg.args[1];
    int player_id = msg.player_id;
    Attackable* other = world.get_from_position(player_id, other_posX, other_posY);
    if (other) { 
        world.characters[msg.player_id]->attack(*other);
        if (!other->is_alive()) {
            std::cout << "ITEMS ANTES: " << world.items.size() << std::endl;
            other->drop_items(world.items);
            // int gold = other->drop_gold();
            std::cout << "ITEMS DESPUES: " << world.items.size() << std::endl;
            clientMessage.id_message = PROTOCOL_KILL_CONFIRM;
        }
        else {
            clientMessage.id_message = PROTOCOL_ATTACK_CONFIRM;
        }
    } 
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}

void ProtocolTranslator::create_character_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world) {
    uint8_t id_race = msg.args[0];
    uint8_t id_class = msg.args[1];

    std::cout << "HAY QUE CREAR UN CLASE: " << (int) id_class << std::endl;
    std::cout << "HAY QUE CREAR UN RAZA: " << (int) id_race << std::endl;

    CharacterClass c = CharacterFactory::make_class(id_class, config);
    Race race = CharacterFactory::make_race(id_race, config);
    Character* character = new Character(msg.player_id, config, c, race, collisionInfo);
    world.add(msg.player_id, character);

    clientMessage.id_message = PROTOCOL_CREATE_CHARACTER_CONFIRM;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}

void ProtocolTranslator::log_off_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world) {
    std::cout << "ALGUIEN SE VA. MUNDO ANTES: " << world.characters.size() << std::endl;
    world.remove_character(msg.player_id);

    clientMessage.id_message = PROTOCOL_LOG_OFF_CONFIRM;
    std::cout << "ALGUIEN SE VA. MUNDO DESPUES: " << world.characters.size() << std::endl;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}

void ProtocolTranslator::create_npc_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world) {
    size_t max_npcs = config["npc"]["max_limit"].asUInt();
    if (world.empty() || world.is_full(max_npcs)) {
        clientMessage.id_message = NOTHING;
        return; 
    }
    int npc_type = msg.args[0];
    NPC* npc = NPCFactory::make_npc(npc_type, config, collisionInfo);
    // std::cout << "NPC CREADO: " << std::endl;
    world.add(msg.player_id, npc);
    clientMessage.id_message = PROTOCOL_CREATE_NPC_CONFIRM;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}

void ProtocolTranslator::update_npcs_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world) {
    world.move_npcs();

    clientMessage.id_message = PROTOCOL_UPDATE_NPCS_CONFIRM;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}

void ProtocolTranslator::update_characters_event(MessageToServer& msg, ProtocolMessage &clientMessage, ServerWorld &world) {
    world.recover_characters();
    
    clientMessage.id_message = PROTOCOL_UPDATE_CHARACTERS_CONFIRM;
    clientMessage.id_player = msg.player_id;
    this->get_world(clientMessage, world);
}


void ProtocolTranslator::get_world(ProtocolMessage& msg, ServerWorld &world) {
    this->get_all_characters(msg, world);
    this->get_all_npcs(msg, world);
    this->get_all_items(msg, world);
}


void ProtocolTranslator::get_all_characters(ProtocolMessage& msg, ServerWorld &world) {
    std::map<uint16_t, Character*>::iterator itr;
    std::vector<ProtocolCharacter> tmp;

    for (itr = world.characters.begin(); itr != world.characters.end(); ++itr) { 
        ProtocolCharacter protocolCharacter;
        itr->second->populate_protocol_character(protocolCharacter);
        tmp.push_back(protocolCharacter);
    }
    msg.characters = tmp;
}


void ProtocolTranslator::get_all_npcs(ProtocolMessage& msg, ServerWorld &world) {
    std::map<uint16_t, NPC*>::iterator itr;
    std::vector<ProtocolNpc> tmp;
    
    for (itr = world.npcs.begin(); itr != world.npcs.end(); ++itr) {
        if (!itr->second->is_alive()) {
            world.remove_npc(itr->first);
            std::cout << "ServerWorld::RemovingDeadNpc" << std::endl;
            continue;
        }
        ProtocolNpc protocolNpc(
            itr->first,
            itr->second->get_id(),
            itr->second->get_body_pos_X(),
            itr->second->get_body_pos_Y(),
            itr->second->get_body_facing()
        );
        tmp.push_back(std::move(protocolNpc));
    }
    msg.npcs = tmp;
}

void ProtocolTranslator::get_all_items(ProtocolMessage& msg, ServerWorld &world) {
    std::vector<ProtocolItem> tmp;

    for (size_t i = 0; i < world.items.size(); ++i) {
        ProtocolItem protocolItem(
            world.items[i].get_id(),
            world.items[i].get_posX(),
            world.items[i].get_posY(),
            world.items[i].get_amount()
        );
        tmp.push_back(std::move(protocolItem));
    }
    msg.items = tmp;
}
