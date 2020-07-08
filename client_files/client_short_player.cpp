
#include "client_common_clothes.h"
#include "client_plate_armor.h"
#include "client_leather_armor.h"
#include "client_short_player.h"
#include "client_blue_robe.h"


ShortPlayer::ShortPlayer(
		SDL_Renderer* gRenderer, 
		const char* head_path, 
		int16_t id, 
		int bodyPosX, 
		int bodyPosY) : Player(bodyPosX, bodyPosY, bodyPosX+3, bodyPosY-12, id, gRenderer) {
	this->load_clothes();
	this->load_helmets();
	this->load_weapons();
	this->load_shields();
	this->playerPicture = new PlayerPicture(gRenderer, head_path);
	this->playerPicture->set_clothes(this->clothes[0]);
	this->equippedPlayer = new EquippedPlayer(playerPicture);
}


void ShortPlayer::load_clothes() {
	Clothes* common = new CommonShortClothes(gRenderer, PLAYER_WIDTH, PLAYER_HEIGHT);
	Clothes* leatherArmor = new LeatherShortArmor(gRenderer, PLAYER_WIDTH, PLAYER_HEIGHT);
	Clothes* plateArmor = new PlateShortArmor(gRenderer, PLAYER_WIDTH, PLAYER_HEIGHT);
	Clothes* blueRobe = new BlueShortRobe(gRenderer, PLAYER_WIDTH, PLAYER_HEIGHT);

	this->clothes.push_back(common);
	this->clothes.push_back(leatherArmor);
	this->clothes.push_back(plateArmor);
	this->clothes.push_back(blueRobe);
}

