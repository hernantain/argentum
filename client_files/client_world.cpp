
#include "client_world.h"



ClientWorld::ClientWorld() {}
    

void ClientWorld::add_player(int16_t id, Player* player) {
    this->players.insert(std::pair<int16_t, Player*> (id, player));
}
