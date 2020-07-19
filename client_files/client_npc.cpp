
#include "client_npc.h"
#include "client_spider.h"
#include "client_skeleton.h"
#include "client_zombie.h"
#include "client_goblin.h"



NPC::NPC(
	uint16_t id,
	uint8_t npc_id, 
	SDL_Renderer* gRenderer, 
	int16_t posX, 
	int16_t posY) : Drawable(id, gRenderer), npc_id(npc_id), posX(posX), posY(posY) {
	
	if (npc_id == 1) this->npcPicture = new Goblin(gRenderer);
	else if (npc_id == 2) this->npcPicture = new Skeleton(gRenderer);
	else if (npc_id == 3) this->npcPicture = new Zombie(gRenderer);
	else this->npcPicture = new Spider(gRenderer);
}

void NPC::set_position(int newPosX, int newPosY, int orientation) {
	// std::unique_lock<std::mutex> lock(this->m);
	this->posX = newPosX;
	this->posY = newPosY;
	this->orientation = orientation;
}

void NPC::render(SDL_Rect &camera) {
	int frame = 0;
	this->npcPicture->render(
		posX - camera.x,
		posY - camera.y,
		gRenderer, 
		orientation, 
		frame // ACA HAY QUE EDITAR
	);
}


NPC::~NPC() {
	delete npcPicture;
}