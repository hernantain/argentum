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
    // print_response_info(msg);
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
    // update_gold_status()
    std::cout << "Depositando OK" << std::endl;
}

void ClientReceiverThread::process_withdraw(ProtocolMessage &msg) {
    // TODO: is the same for the deposit and withdraw -> make just One Method
    // update_gold_status()
    std::cout << "Retirando OK" << std::endl;
}

void ClientReceiverThread::process_resurrection(ProtocolMessage &msg) {
    update_bars(msg);
    world.update_player_alive_status(msg);
    std::cout << "Resucitando OK" << std::endl;
}

void ClientReceiverThread::process_healing(ProtocolMessage &msg) {
    update_bars(msg);
    std::cout << "Curando OK" << std::endl;
}

void ClientReceiverThread::process_equip_helmet(ProtocolMessage &msg) {
    int i = msg.find(msg.id_player);
    bool is_alive = msg.characters[i].alive;
    std::cout << "HELMET ID: " << (int) msg.characters[i].helmetId << std::endl;
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
    std::cout << "EQUIP WEAPON" << std::endl;
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
    std::cout << "ARMOR ID: " << (int) msg.characters[i].armorId << std::endl;
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
    std::cout << "EQUIP WEAPON" << std::endl;
    int i = msg.find(msg.id_player);
    bool is_alive = msg.characters[i].alive;
    if (i != -1 && is_alive)
        world.player_set_weapon(msg.id_player, msg.characters[i].weaponId);
}

void ClientReceiverThread::process_equip_potion(ProtocolMessage &msg) {
    std::cout << "EQUIP POTION" << std::endl;
    update_bars(msg);
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

    std::cout << "ITEMS DESPUES: " << world.items.size() << std::endl;
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
    // update_bars(msg);
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
    std::cout << "DEATH: " << (int) msg.id_player << std::endl;
    int i = msg.find(this->player_id);
    std::cout << "i es: " << i << std::endl;
    std::cout << "SOY PLAYER: " << player_id << " Y estoy: " << ((msg.characters[i].alive) ? "vivo!" : "muerto") << std::endl;
    std::cout << "PLAYER: " << msg.characters[i].id << " ALIVE? " << msg.characters[i].alive << std::endl;
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
    }
}

void ClientReceiverThread::process_log_off(ProtocolMessage &msg) {
    if (msg.id_player == this->player_id) {
        // TEAR DOWN LOGIC
        std::cout << "CERRANDO RECEIVERS THREAD" << std::endl;
        this->running = false;
    } else {
        world.remove_player(msg.id_player);
        std::cout << "BORRANDO OTRO JUGADOR" << std::endl;
    }
}

void ClientReceiverThread::print_response_info(ProtocolMessage &msg) {
    std::cout << "TAMANIO MUNDO: " << world.players.size() << std::endl;
    for (unsigned int i = 0; i < msg.characters.size(); ++i) {
        std::cout << "PROT CHARACTER ID " << (int) msg.characters[i].id << std::endl;
        std::cout << "PROT CHARACTER ID RACE " << (int) msg.characters[i].id_race << std::endl;
        std::cout << "PROT CHARACTER ID CLASE " << (int) msg.characters[i].id_class << std::endl;
        std::cout << "PROT CHARACTER bodyposX " << (int) msg.characters[i].bodyPosX << std::endl;
        std::cout << "PROT CHARACTER bodyposY " << (int) msg.characters[i].bodyPosY << std::endl;
        std::cout << "PROT CHARACTER ORIENTAT " << (int) msg.characters[i].orientation << std::endl;
        std::cout << "PROT CHARACTER MANA " << (int) msg.characters[i].mana << std::endl;
        std::cout << "PROT CHARACTER MAX_MANA " << (int) msg.characters[i].max_mana << std::endl;
        std::cout << "PROT CHARACTER LIFE " << (int) msg.characters[i].life << std::endl;
        std::cout << "PROT CHARACTER MAX_LIFE " << (int) msg.characters[i].max_life << std::endl;
        std::cout << "PROT CHARACTER EXPERIEN " << (int) msg.characters[i].experience << std::endl;
        std::cout << "PROT CHARACTER MAX EXP " << (int) msg.characters[i].max_experience << std::endl;
        std::cout << "PROT CHARACTER ALIVE " << (int) msg.characters[i].alive << std::endl;
        std::cout << std::endl;
    }
}
