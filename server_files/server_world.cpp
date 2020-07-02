
#include "server_world.h"



ServerWorld::ServerWorld() {}


Character* ServerWorld::get(int16_t message_id) {
    return this->characters[message_id];
}


bool ServerWorld::empty() {
    return (this->characters.size() == 0);
}


void ServerWorld::add(int16_t id, Character* character) {
    this->characters.insert(std::pair<int16_t, Character*> (id, character));

}