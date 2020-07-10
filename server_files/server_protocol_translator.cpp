#include <stdint.h>
#include <iostream>

#include "server_world.h"
#include "server_protocol_translator.h"

ProtocolTranslator::ProtocolTranslator(
    Json::Value &config, 
    CollisionInfo &collisionInfo) : config(config),
                                    collisionInfo(collisionInfo) {}


void ProtocolTranslator::translate(ProtocolMessage& msg, ServerWorld& world) {
    int code = msg.id_message;
    switch (code) {
        case PROTOCOL_CREATE_CHARACTER: return create_character_event(msg, world);
        case PROTOCOL_CREATE_NPC: return create_npc_event(msg, world);
        case PROTOCOL_UPDATE_NPCS: return update_npcs_event(msg, world);
        case PROTOCOL_UPDATE_CHARACTERS: return update_characters_event(msg, world);
        case PROTOCOL_MOVE_RIGHT: return move_right_event(msg, world);
        case PROTOCOL_MOVE_LEFT: return move_left_event(msg, world);
        case PROTOCOL_MOVE_TOP: return move_top_event(msg, world);
        case PROTOCOL_MOVE_DOWN: return move_down_event(msg, world);
        case PROTOCOL_EQUIP_HELMET: return equip_helmet_event(msg, world);
        case PROTOCOL_EQUIP_ARMOR: return equip_armor_event(msg, world);
        case PROTOCOL_EQUIP_WEAPON: return equip_weapon_event(msg, world);
        case PROTOCOL_EQUIP_SHIELD: return equip_shield_event(msg, world);
        case PROTOCOL_MOVE_STOP: return stop_moving(msg, world);
        case PROTOCOL_ATTACK: return attack_event(msg, world);
        case PROTOCOL_MEDITATION: return meditation_event(msg, world);
        case PROTOCOL_TAKE_ITEM: return take_item_event(msg, world);
        case PROTOCOL_LOG_OFF: return log_off_event(msg, world);
    }
}

void ProtocolTranslator::equip_shield_event(ProtocolMessage &msg, ServerWorld &world) {

    int shield_id = msg.characters[0].shieldId;
    ShieldFactory factory;
    Shield shield = factory.make_shield(shield_id, config);
    world.characters[msg.id_player]->equip_shield(shield);
    msg.id_message = PROTOCOL_SHIELD_CONFIRM;
}

void ProtocolTranslator::equip_weapon_event(ProtocolMessage &msg, ServerWorld &world) {
    int weapon_id = msg.characters[0].weaponId;
    WeaponFactory factory;
    Weapon weapon = factory.make_weapon(weapon_id, config);
    world.characters[msg.id_player]->equip_weapon(weapon);
    msg.id_message = PROTOCOL_WEAPON_CONFIRM;
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

void ProtocolTranslator::stop_moving(ProtocolMessage &msg, ServerWorld &world) {

    world.characters[msg.id_player]->stop_moving();
    this->get_world(msg, world);
    msg.id_message = PROTOCOL_MOVE_CONFIRM;
}


void ProtocolTranslator::move_right_event(ProtocolMessage &msg, ServerWorld &world) {

    // world.characters[msg.id_player]->move_right();
    world.move_character_right(msg.id_player);
    this->get_world(msg, world);
    msg.id_message = PROTOCOL_MOVE_CONFIRM;
}


void ProtocolTranslator::move_left_event(ProtocolMessage &msg, ServerWorld &world) {

    // world.characters[msg.id_player]->move_left();
    world.move_character_left(msg.id_player);
    this->get_world(msg, world);

    msg.id_message = PROTOCOL_MOVE_CONFIRM;
}


void ProtocolTranslator::move_top_event(ProtocolMessage &msg, ServerWorld &world) {

    world.move_character_top(msg.id_player);
    // world.characters[msg.id_player]->move_top();
    this->get_world(msg, world);

    msg.id_message = PROTOCOL_MOVE_CONFIRM;
}


void ProtocolTranslator::move_down_event(ProtocolMessage &msg, ServerWorld &world) {

    world.move_character_down(msg.id_player);
    // world.characters[msg.id_player]->move_down();
    this->get_world(msg, world);
    msg.id_message = PROTOCOL_MOVE_CONFIRM;
}

void ProtocolTranslator::take_item_event(ProtocolMessage &msg, ServerWorld &world) {
    // int item_id = msg.characters[0].itemId;
    // ItemFactory factory;
    // Item item = factory.make_itemt(item_id, config);
    // world.characters[msg.id_player]->take_item(item);
    // msg.id_message = PROTOCOL_TAKE_ITEM_CONFIRM;
}

void ProtocolTranslator::meditation_event(ProtocolMessage &msg, ServerWorld &world) {
    world.characters[msg.id_player]->meditate();
    // Here we might use the following and add a "meditating" boolean on the prot
    // this->get_all_characters(msg, world);
    std::cout << "Meditando" << std::endl;
    msg.id_message = PROTOCOL_MEDITATE_CONFIRM;
}

void ProtocolTranslator::attack_event(ProtocolMessage &msg, ServerWorld &world) {
    int other_posX = msg.characters[0].otherPosX;
    int other_posY = msg.characters[0].otherPosY;
    int player_id = msg.id_player;
    Attackable* other = world.get_from_position(player_id, other_posX, other_posY);
    if (other) { 
        world.characters[msg.id_player]->attack(*other);
        // if (!other->is_alive()) {
        //     std::vector<int> drop_items = other->drop_items();
        //     int gold = other->drop_gold();
        // }
        msg.id_message = PROTOCOL_ATTACK_CONFIRM;
    } 
    this->get_world(msg, world);
}

void ProtocolTranslator::create_character_event(ProtocolMessage& msg, ServerWorld &world) {
    int id_class = msg.characters[0].id_class;
    int id_race = msg.characters[0].id_race;
    CharacterFactory factory;
    CharacterClass c = factory.make_class(id_class, config);
    Race race = factory.make_race(id_race, config);
    Character* character = new Character(msg.id_player, config, c, race, collisionInfo);
    world.add(msg.id_player, character);
    msg.id_message = PROTOCOL_CREATE_CHARACTER_CONFIRM;
    this->get_world(msg, world);
}

void ProtocolTranslator::log_off_event(ProtocolMessage& msg, ServerWorld &world) {
    std::cout << "ALGUIEN SE VA. MUNDO ANTES: " << world.characters.size() << std::endl;
    world.remove_character(msg.id_player);
    msg.id_message = PROTOCOL_LOG_OFF_CONFIRM;
    std::cout << "ALGUIEN SE VA. MUNDO DESPUES: " << world.characters.size() << std::endl;
    this->get_world(msg, world);
}

void ProtocolTranslator::create_npc_event(ProtocolMessage& msg, ServerWorld &world) {
    if (world.empty()) {
        msg.id_message = NOTHING;
        return; 
    }
    
    int npc_id = msg.npcs[0].npc_type;
    NPCFactory factory;
    NPC* npc = factory.make_npc(npc_id, config, collisionInfo);
    std::cout << "NPC CREADO: " << std::endl;
    world.add(msg.id_player, npc);
    this->get_world(msg, world);
    msg.id_message = PROTOCOL_CREATE_NPC_CONFIRM;

}

void ProtocolTranslator::update_npcs_event(ProtocolMessage& msg, ServerWorld &world) {
    // forEach npc, Npc move, check if alive. if ! count ++ para dsp spawnear count npcs
    // canAttack
    world.move_npcs();
    this->get_world(msg, world);
    msg.id_message = PROTOCOL_UPDATE_NPCS_CONFIRM;
}

void ProtocolTranslator::update_characters_event(ProtocolMessage& msg, ServerWorld &world) {
    world.recover_characters();
    this->get_world(msg, world);
    msg.id_message = PROTOCOL_UPDATE_CHARACTERS_CONFIRM;
}


void ProtocolTranslator::get_world(ProtocolMessage& msg, ServerWorld &world) {
    this->get_all_characters(msg, world);
    this->get_all_npcs(msg, world);
    this->get_all_items(msg, world);
}


void ProtocolTranslator::get_all_characters(ProtocolMessage& msg, ServerWorld &world) {
    std::map<int16_t, Character*>::iterator itr;
    std::vector<ProtocolCharacter> tmp;

    for (itr = world.characters.begin(); itr != world.characters.end(); ++itr) { 
        ProtocolCharacter protocolCharacter;
        itr->second->populate_protocol_character(protocolCharacter);
        tmp.push_back(std::move(protocolCharacter));
    }
    msg.characters = tmp;
}


void ProtocolTranslator::get_all_npcs(ProtocolMessage& msg, ServerWorld &world) {
    std::map<int16_t, NPC*>::iterator itr;
    std::vector<ProtocolNpc> tmp;
    
    for (itr = world.npcs.begin(); itr != world.npcs.end(); ++itr) { 
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
            world.items[i]->get_id(),
            world.items[i]->get_posX(),
            world.items[i]->get_posY(),
            world.items[i]->get_amount()
        );
        tmp.push_back(std::move(protocolItem));
    }
    msg.items = tmp;
}

