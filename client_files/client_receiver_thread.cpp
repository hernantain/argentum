#include <msgpack.hpp>

#include "client_receiver_thread.h"
#include "client_drawable.h"

#define DEFAULT_EQUIPMENT 0

ClientReceiverThread::ClientReceiverThread(
    Socket &skt, 
    ClientWorld &world,
    SDL_Rect &camera,
    InfoView &infoView,
    SoundManager &soundManager,
    uint16_t player_id) : skt(skt), 
                        world(world),
                        camera(camera),
                        infoView(infoView),
                        soundManager(soundManager),
                        player_id(player_id),
                        running(true) {}



void ClientReceiverThread::run() {
    while (this->running) {
        ProtocolMessage msg;
        msgpack::unpacker pac;
        this->skt >> pac;
        msgpack::object_handle oh;
        pac.next(oh);
        msgpack::object obj = oh.get();
        obj.convert(msg);
        this->process_response(msg);
    }
}


void ClientReceiverThread::process_response(ProtocolMessage &msg) {
    // std::cout << "PROCESANDO RESPUESTA: " << msg.id_message << std::endl;
    if (msg.id_message == PROTOCOL_MOVE_CONFIRM) this->process_move(msg);
    if (msg.id_message == PROTOCOL_DEPOSIT_CONFIRM) this->process_deposit(msg);
    if (msg.id_message == PROTOCOL_WITHDRAW_CONFIRM) this->process_withdraw(msg);
    if (msg.id_message == PROTOCOL_RESURRECT_CONFIRM) this->process_resurrection(msg);
    if (msg.id_message == PROTOCOL_HEAL_CONFIRM) this->process_healing(msg);
    if (msg.id_message == PROTOCOL_ATTACK_CONFIRM) this->process_attack(msg);
    if (msg.id_message == PROTOCOL_KILL_CONFIRM) this->process_death(msg);
    if (msg.id_message == PROTOCOL_HELMET_CONFIRM) this->process_equip_helmet(msg);
    if (msg.id_message == PROTOCOL_ARMOR_CONFIRM) this->process_equip_armor(msg);
    if (msg.id_message == PROTOCOL_WEAPON_CONFIRM) this->process_equip_weapon(msg);
    if (msg.id_message == PROTOCOL_SHIELD_CONFIRM) this->process_equip_shield(msg);
    if (msg.id_message == PROTOCOL_HELMET_DEFAULT) this->process_default_helmet(msg);
    if (msg.id_message == PROTOCOL_ARMOR_DEFAULT) this->process_default_armor(msg);
    if (msg.id_message == PROTOCOL_WEAPON_DEFAULT) this->process_default_weapon(msg);
    if (msg.id_message == PROTOCOL_SHIELD_DEFAULT) this->process_default_shield(msg);
    if (msg.id_message == PROTOCOL_EQUIP_POTION_CONFIRM) this->process_equip_potion(msg);
    if (msg.id_message == PROTOCOL_MEDITATE_CONFIRM) this->process_meditation(msg);
    if (msg.id_message == PROTOCOL_TAKE_ITEM_CONFIRM) this->process_take_item(msg);
    if (msg.id_message == PROTOCOL_DROP_ITEM_CONFIRM) this->process_drop_item(msg);
    if (msg.id_message == PROTOCOL_CREATE_CHARACTER_CONFIRM) this->process_create_player(msg);
    if (msg.id_message == PROTOCOL_LOG_OFF_CONFIRM) this->process_log_off(msg);
    if (msg.id_message == PROTOCOL_CREATE_NPC_CONFIRM) this->process_create_npc(msg);
    if (msg.id_message == PROTOCOL_UPDATE_NPCS_CONFIRM) this->process_move_npcs(msg);
    if (msg.id_message == PROTOCOL_UPDATE_CHARACTERS_CONFIRM) this->process_recover_characters(msg);
    if (msg.id_player == this->player_id)
        world.players[this->player_id]->set_camera(camera);
}


void ClientReceiverThread::process_move(ProtocolMessage &msg) {
    int i = msg.find(msg.id_player);
    if (i != -1)
        world.move_player(msg.id_player, msg.characters[i].bodyPosX, msg.characters[i].bodyPosY, msg.characters[i].orientation);
}

void ClientReceiverThread::process_deposit(ProtocolMessage &msg) {
    int i = msg.find(msg.id_player);
    if (i != -1) 
        infoView.set_gold(msg.characters[i].gold);
}

void ClientReceiverThread::process_withdraw(ProtocolMessage &msg) {
    int i = msg.find(msg.id_player);
    if (i != -1) 
        infoView.set_gold(msg.characters[i].gold);
}

void ClientReceiverThread::process_resurrection(ProtocolMessage &msg) {
    update_bars(msg);
    world.update_player_alive_status(msg);
}

void ClientReceiverThread::process_healing(ProtocolMessage &msg) {
    update_bars(msg);
}

void ClientReceiverThread::process_equip_helmet(ProtocolMessage &msg) {
    int i = msg.find(msg.id_player);
    bool is_alive = msg.characters[i].alive;
    if (i != -1 && is_alive)
        world.player_set_helmet(msg.id_player, msg.characters[i].helmetId);
}

void ClientReceiverThread::process_default_armor(ProtocolMessage &msg) {
    int i = msg.find(msg.id_player);
    bool is_alive = msg.characters[i].alive;
    if (i != -1 && is_alive)
        world.player_set_armor(msg.id_player, DEFAULT_EQUIPMENT);
}

void ClientReceiverThread::process_default_shield(ProtocolMessage &msg) {
    int i = msg.find(msg.id_player);
    bool is_alive = msg.characters[i].alive;
    if (i != -1 && is_alive)
        world.player_set_shield(msg.id_player, DEFAULT_EQUIPMENT);
}

void ClientReceiverThread::process_default_weapon(ProtocolMessage &msg) {
    int i = msg.find(msg.id_player);
    bool is_alive = msg.characters[i].alive;
    if (i != -1 && is_alive)
        world.player_set_weapon(msg.id_player, DEFAULT_EQUIPMENT);
}

void ClientReceiverThread::process_default_helmet(ProtocolMessage &msg) {
    int i = msg.find(msg.id_player);
    bool is_alive = msg.characters[i].alive;
    if (i != -1 && is_alive)
        world.player_set_helmet(msg.id_player, DEFAULT_EQUIPMENT);
}

void ClientReceiverThread::process_equip_armor(ProtocolMessage &msg) {
    int i = msg.find(msg.id_player);
    bool is_alive = msg.characters[i].alive;
    if (i != -1 && is_alive)
        world.player_set_armor(msg.id_player, msg.characters[i].armorId);
}

void ClientReceiverThread::process_equip_shield(ProtocolMessage &msg) {
    int i = msg.find(msg.id_player);
    bool is_alive = msg.characters[i].alive;
    if (i != -1 && is_alive)    
        world.player_set_shield(msg.id_player, msg.characters[i].shieldId);
}

void ClientReceiverThread::process_equip_weapon(ProtocolMessage &msg) {
    int i = msg.find(msg.id_player);
    bool is_alive = msg.characters[i].alive;
    if (i != -1 && is_alive)
        world.player_set_weapon(msg.id_player, msg.characters[i].weaponId);
}

void ClientReceiverThread::process_equip_potion(ProtocolMessage &msg) {
    std::cout << "POTION CONFIRM" << std::endl;
    update_bars(msg);
    if (msg.id_player == this->player_id) {
        uint8_t itemId = world.get_equipped_potion(this->player_id);
        infoView.decreaseItem(itemId);
    }
}

void ClientReceiverThread::process_meditation(ProtocolMessage &msg) {
    update_bars(msg);
    // world.update_player_meditation_status(msg);
}


void ClientReceiverThread::process_create_player(ProtocolMessage &msg) {
    int i = msg.find(msg.id_player);
    if (i != -1) {
        std::cout << "HAY QUE CREAR OTRO PLAYER: " << msg.id_player << "EN POS: " << i << std::endl;
        world.add_player(msg.characters[i]);
    }
}


void ClientReceiverThread::process_create_npc(ProtocolMessage &msg) {
    int i = msg.find_npc(msg.id_player);
    if (i != -1)
        world.add_npc(msg.npcs[i]);
}

void ClientReceiverThread::process_take_item(ProtocolMessage &msg) {
    std::cout << "ITEMS ANTES: " << world.items.size() << std::endl;
    Item* item = world.update_items(msg);
    if (item == NULL) 
        return;
    
    std::cout << "No es NULL" << std::endl;
    if ((msg.id_player == this->player_id) && (item->get_id() != 20)) {
        std::cout << "Agregando a infoview" << std::endl;        
        this->infoView.add_item(item);

    } else { 
        delete item;
    }

    int i = msg.find(msg.id_player);
    if (i != -1) 
        infoView.set_gold(msg.characters[i].gold);

    std::cout << "ITEMS DESPUES: " << world.items.size() << std::endl;
    std::cout << std::endl;
}

void ClientReceiverThread::process_drop_item(ProtocolMessage &msg) {
    if (msg.id_player == this->player_id) {
        uint8_t itemId = world.get_dropped_item(this->player_id);
        infoView.dropItem(itemId);
    }

    world.add_items(msg);
}

void ClientReceiverThread::process_move_npcs(ProtocolMessage &msg) {
    int i = msg.find(this->player_id);
    if (i != -1 && !msg.characters[i].alive)
        infoView.clear_items();

    world.update_npcs(msg);
    world.update_player_alive_status(msg);
    world.add_items(msg);
    update_bars(msg);
}

void ClientReceiverThread::process_recover_characters(ProtocolMessage &msg) {
    int i = msg.find(this->player_id);
    bool is_alive = msg.characters[i].alive;
    if (i != -1 && is_alive) {
        this->infoView.set_life(msg.characters[i].life, msg.characters[i].max_life);
        this->infoView.set_mana(msg.characters[i].mana, msg.characters[i].max_mana);
    }
}

void ClientReceiverThread::process_attack(ProtocolMessage &msg) {
    update_bars(msg);
    int i = msg.find(this->player_id);
    if (msg.id_player == this->player_id)
        soundManager.set_sound(msg.characters[i].weaponId);
}

void ClientReceiverThread::process_death(ProtocolMessage &msg) {
    int i = msg.find(this->player_id);
    if (!msg.characters[i].alive)
        infoView.clear_items();
        
    update_bars(msg);
    world.update_dead_npcs(msg);
    world.update_player_alive_status(msg);
    world.add_items(msg);
}

void ClientReceiverThread::update_bars(ProtocolMessage &msg) {
    int i = msg.find(this->player_id);
    if (i != -1) {
        this->infoView.set_life(msg.characters[i].life, msg.characters[i].max_life);
        this->infoView.set_mana(msg.characters[i].mana, msg.characters[i].max_mana);
        this->infoView.set_experience(msg.characters[i].experience, msg.characters[i].max_experience);
        this->infoView.set_level(msg.characters[i].level);
    }
}


void ClientReceiverThread::process_log_off(ProtocolMessage &msg) {
    if (msg.id_player == this->player_id) {
        // TEAR DOWN LOGIC
        std::cout << "CERRANDO RECEIVERS THREAD" << std::endl;
        this->running = false;
    } else {
        world.remove_player(msg.id_player);
    }
}

