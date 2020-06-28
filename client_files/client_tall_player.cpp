
#include "client_common_clothes.h"
#include "client_plate_armor.h"
#include "client_leather_armor.h"
#include "client_tall_player.h"

TallPlayer::TallPlayer(SDL_Renderer* gRenderer, const char* head_path) : Player(25, 25, 29, 15) {
	this->load_clothes(gRenderer);
	this->load_helmets(gRenderer);
	this->playerPicture = new PlayerPicture(gRenderer, head_path);
	this->playerPicture->set_clothes(this->clothes[0]);
	this->equippedPlayer = new EquippedPlayer(playerPicture);
}



void TallPlayer::load_clothes(SDL_Renderer* gRenderer) {
	Clothes* common = new CommonTallClothes(gRenderer, PLAYER_WIDTH, PLAYER_HEIGHT);
	Clothes* leatherArmor = new LeatherTallArmor(gRenderer, PLAYER_WIDTH, PLAYER_HEIGHT);
	Clothes* plateArmor = new PlateTallArmor(gRenderer, PLAYER_WIDTH, PLAYER_HEIGHT);
	// Clothes* blueRobe = new BlueTallRobe(gRenderer, PLAYER_WIDTH, PLAYER_HEIGHT);
	this->clothes.push_back(common);
	this->clothes.push_back(leatherArmor);
	this->clothes.push_back(plateArmor);
	// this->clothes.push_back(blueRobe);

}
