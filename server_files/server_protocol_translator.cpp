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


ProtocolMessage ProtocolTranslator::translate(ProtocolMessage& msg, ServerWorld& world) {
    int code = msg.id_message;
    // Character character = world.get(msg.id_player);
    switch (code) {
        case 65: return create_character(msg, world);
        case PROTOCOL_MOVE: return move_event(msg, world);
        case PROTOCOL_EQUIP_HELMET: return equip_helmet_event(msg, world);
        case PROTOCOL_EQUIP_ARMOR: return equip_armor_event(msg, world);
    }
    return std::move(msg);
}

ProtocolMessage ProtocolTranslator::equip_armor_event(ProtocolMessage &msg, ServerWorld &world) {
    // int armor_id = msg.character.armorId;
    // ArmorFactory factory;
    // Armor armor = factory.make_armor(armor_id, config);
    // character.equip_armor(armor);
    // msg.id = PROTOCOL_ARMOR_CONFIRM;

    // std::cout << "ID: " << msg.id << std::endl;
    // std::cout << "Updated Armor ID: " << msg.character.armorId << std::endl;

    int armor_id = msg.characters[0].armorId;
    ArmorFactory factory;
    Armor armor = factory.make_armor(armor_id, config);
    world.characters[msg.id_player]->equip_armor(armor);
    msg.id_message = PROTOCOL_ARMOR_CONFIRM;

    // std::cout << "ID: " << msg.id << std::endl;
    // std::cout << "Updated Armor ID: " << msg.character.armorId << std::endl;

    return std::move(msg);
}


ProtocolMessage ProtocolTranslator::equip_helmet_event(ProtocolMessage &msg, ServerWorld &world) {
    // int helmet_id = msg.character.helmetId;
    // HelmetFactory factory;
    // Helmet helmet = factory.make_helmet(helmet_id, config);
    // character.equip_helmet(helmet);
    // msg.id = PROTOCOL_HELMET_CONFIRM;

    // std::cout << "ID: " << msg.id << std::endl;
    // std::cout << "Updated Helmet ID: " << msg.character.helmetId << std::endl;
    int helmet_id = msg.characters[0].helmetId;
    HelmetFactory factory;
    Helmet helmet = factory.make_helmet(helmet_id, config);
    world.characters[msg.id_player]->equip_helmet(helmet);
    msg.id_message = PROTOCOL_HELMET_CONFIRM;

    // std::cout << "ID: " << msg.id << std::endl;
    // std::cout << "Updated Helmet ID: " << msg.character.helmetId << std::endl;

    return std::move(msg);
}


ProtocolMessage ProtocolTranslator::move_event(ProtocolMessage &msg, ServerWorld &world) {
    // int velX = msg.character.velX;
    // int velY = msg.character.velY;

    // if (velX > 0) {
    //     character.move_right(velX);
    // }
    // if (velX < 0) {
    //     character.move_left(velX);;
    // }
    // if (velY > 0) {
    //     character.move_top(velY);
    // }
    // if (velY < 0) {
    //     character.move_down(velY);
    // }
    // msg.character.bodyPosX = character.get_body_pos_X();
    // msg.character.headPosX = character.get_head_pos_X();
    // msg.character.bodyPosY = character.get_body_pos_Y();
    // msg.character.headPosY = character.get_head_pos_Y();
    // msg.id = PROTOCOL_MOVE_CONFIRM;

    // std::cout << "ID: " << msg.id << std::endl;
    // std::cout << "Updated BODY pos X: " << msg.character.bodyPosX << std::endl;
    // std::cout << "Updated BODY pos Y: " << msg.character.bodyPosY << std::endl;
    // std::cout << "Updated HEAD pos X: " << msg.character.headPosX << std::endl;
    // std::cout << "Updated HEAD pos Y: " << msg.character.headPosY << std::endl;

    int velX = msg.characters[0].velX;
    int velY = msg.characters[0].velY;

    if (velX > 0) {
        world.characters[msg.id_player]->move_right(velX);
    }
    if (velX < 0) {
        world.characters[msg.id_player]->move_left(velX);;
    }
    if (velY > 0) {
        world.characters[msg.id_player]->move_top(velY);
    }
    if (velY < 0) {
        world.characters[msg.id_player]->move_down(velY);
    }
    msg.characters[0].bodyPosX = world.characters[msg.id_player]->get_body_pos_X();
    msg.characters[0].headPosX = world.characters[msg.id_player]->get_head_pos_X();
    msg.characters[0].bodyPosY = world.characters[msg.id_player]->get_body_pos_Y();
    msg.characters[0].headPosY = world.characters[msg.id_player]->get_head_pos_Y();
    msg.id_message = PROTOCOL_MOVE_CONFIRM;

    return std::move(msg);
}


ProtocolMessage ProtocolTranslator::create_character(ProtocolMessage& msg, ServerWorld &world) {
    
    Elf race(config);
    Cleric c(config);
    Character* character = new Character(msg.id_player, config, c, race, collisionInfo);
    world.add(msg.id_player, character);

    msg.id_message = 66;

    msg.characters[0].bodyPosX += 200;
    msg.characters[0].bodyPosY += 200;
    msg.characters[0].headPosX += 200;
    msg.characters[0].headPosX += 200;


    return std::move(msg);
    // std::map<int16_t, Character*>::iterator itr;  
    // for (itr = world.characters.begin(); itr != world.characters.end(); ++itr) { 
    //     ProtocolCharacter protocolCharacter(character);
    //     msg.characters.push_back(protocolCharacter);
    // }

}
