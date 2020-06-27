#include <stdint.h>
#include <iostream>
#include "server_protocol_translator.h"

ProtocolTranslator::ProtocolTranslator() {}

ProtocolMessage ProtocolTranslator::translate(ProtocolMessage& msg, Character& character) {
    int code = msg.id;
    switch (code) {
        case PROTOCOL_MOVE: return move_event(msg, character);
        // case PROTOCOL_ATTACK: return attack_event();
    }
    return std::move(msg);
}

ProtocolMessage ProtocolTranslator::move_event(ProtocolMessage &msg, Character& character) {
    int velX = msg.character.velX;
    int velY = msg.character.velY;

    if (velX > 0) {
        character.move_right(velX);
        std::cout << "Me muevo pa la derecha" << std::endl;
    }
    if (velX < 0) {
        character.move_left(velX);;
        std::cout << "Me muevo pa la izq" << std::endl;
    }
    if (velY > 0) {
        character.move_top(velY);
        std::cout << "Me muevo pa arriba" << std::endl;
    }
    if (velY < 0) {
        character.move_down(velY);
        std::cout << "Me muevo pa abajo" << std::endl;
    }
    msg.character.bodyPosX = character.get_body_pos_X();
    msg.character.headPosX = character.get_head_pos_X();
    msg.character.bodyPosY = character.get_body_pos_Y();
    msg.character.headPosY = character.get_head_pos_Y();
    msg.id = PROTOCOL_MOVE_CONFIRM;

    std::cout << "ID: " << msg.id << std::endl;
    std::cout << "Updated BODY pos X: " << msg.character.bodyPosX << std::endl;
    std::cout << "Updated BODY pos Y: " << msg.character.bodyPosY << std::endl;
    std::cout << "Updated HEAD pos X: " << msg.character.headPosX << std::endl;
    std::cout << "Updated HEAD pos Y: " << msg.character.headPosY << std::endl;

    return std::move(msg);
}

