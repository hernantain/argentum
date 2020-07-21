
#include "client_hood.h"
#include "client_magic_hat.h"
#include "client_iron_helmet.h"
#include "client_axe.h"
#include "client_hammer.h"
#include "client_baculo_nudoso.h"
#include "client_baculo_engarzado.h"
#include "client_compound_bow.h"
#include "client_simple_bow.h"
#include "client_iron_shield.h"
#include "client_turtle_shield.h"
#include "client_ash_staff.h"
#include "client_sword.h"
#include "client_player.h"
#include <iostream>

#include "../common_files/common_message_to_server.h"

Player::Player(
    int16_t bodyPosX, 
    int16_t bodyPosY, 
    int16_t headPosX, 
    int16_t headPosY,
	uint16_t id,
	SDL_Renderer* gRenderer) : Drawable(id, gRenderer),
								bodyPosX(bodyPosX), 
								bodyPosY(bodyPosY),
								headPosX(headPosX),
								headPosY(headPosY) {
	this->headOffsetX = headPosX - bodyPosX;
	this->headOffsetY = headPosY - bodyPosY;
	this->alive = true;
	this->orientation = STANDING;
	this->armorId = 0;
	this->weaponId = 0;
	this->shieldId = 0;
	this->helmetId = 0;
	this->potionId = 0;
	this->itemId = 0;
	this->ghost = NULL;
}


    
void Player::set_camera(SDL_Rect &camera) {

	camera.x = ( this->bodyPosX +  18 ) - camera.w / 2;
	camera.y = ( this->bodyPosY + 18 ) - camera.h / 2;

	//Keep the camera in bounds
	if( camera.x < 0 )
		camera.x = 0;
	
	if( camera.y < 0 ) 
		camera.y = 0;
	
	if( camera.x > MAP_SIZE - camera.w )
		camera.x = MAP_SIZE - camera.w;
	
	if( camera.y > MAP_SIZE - camera.h )
		camera.y = MAP_SIZE - camera.h; 
}

void Player::set_position(int16_t newBodyPosX, int16_t newBodyPosY, int orientation) {
	this->orientation = orientation;
	this->bodyPosX = newBodyPosX;
	this->bodyPosY = newBodyPosY;
	this->headPosX = newBodyPosX+this->headOffsetX;
	this->headPosY = newBodyPosY+this->headOffsetY;
}


void Player::update_alive_status(bool alive) {
	this->alive = alive;
	if (!this->alive) {
		this->equippedPlayer->setHelmet(NULL);
		this->equippedPlayer->setShield(NULL);
		this->equippedPlayer->setWeapon(NULL);
		this->playerPicture->set_clothes(this->clothes[0]);
		armorId = 0;
		shieldId = 0;
		weaponId = 0;
		helmetId = 0;
		potionId = 0;
		itemId = 0;
	}
}


void Player::render(SDL_Rect &camera, int &it) {
	if (this->alive) {
		equippedPlayer->render(
			bodyPosX - camera.x, 
			bodyPosY - camera.y, 
			headPosX - camera.x, 
			headPosY - camera.y, 
			gRenderer, 
			this->orientation, 
			it
		);
	} else {
		ghost = (ghost != NULL) ? ghost : new Ghost(this->gRenderer);
		ghost->render(
			bodyPosX - camera.x, 
			bodyPosY - camera.y, 
			gRenderer, 
			orientation, 
			it
		);
	}
}



void Player::load_helmets() {
	Helmet* hood = new Hood(gRenderer);
	Helmet* ironHelmet = new IronHelmet(gRenderer);
	Helmet* magicHat = new MagicHat(gRenderer);
	this->helmets.push_back(hood);
	this->helmets.push_back(ironHelmet);
	this->helmets.push_back(magicHat);	
}


void Player::load_shields() {
	IronShield* ironShield = new IronShield(gRenderer);
	TurtleShield* turtleShield = new TurtleShield(gRenderer);
	this->shields.push_back(ironShield); 
	this->shields.push_back(turtleShield);
}


void Player::load_weapons() {
	Weapon* sword = new Sword(gRenderer);
	Axe* axe = new Axe(gRenderer);
	Hammer* hammer = new Hammer(gRenderer);
	BaculoEngarzado* baculoEngarzado = new BaculoEngarzado(gRenderer);
	BaculoNudoso* baculoNudoso = new BaculoNudoso(gRenderer);
	CompoundBow* compoundBow = new CompoundBow(gRenderer);
	SimpleBow* simpleBow = new SimpleBow(gRenderer);
	AshStaff* ashStaff = new AshStaff(gRenderer);
	this->weapons.push_back(sword);
	this->weapons.push_back(axe);
	this->weapons.push_back(hammer);
	this->weapons.push_back(baculoNudoso);
	this->weapons.push_back(baculoEngarzado);
	this->weapons.push_back(compoundBow);
	this->weapons.push_back(simpleBow);
	this->weapons.push_back(ashStaff);
}

void Player::set_weapon(int weaponId) {
	if (weaponId == SWORD_CODE) {
		this->equippedPlayer->setWeapon(this->weapons[0]);
	} else if (weaponId == AXE_CODE) {
		this->equippedPlayer->setWeapon(this->weapons[1]);
	} else if (weaponId == HAMMER_CODE) {
		this->equippedPlayer->setWeapon(this->weapons[2]);
	} else if (weaponId == ASH_STAFF_CODE) {
		this->equippedPlayer->setWeapon(this->weapons[7]);
	} else if (weaponId == GNARLED_STAFF_CODE) {
		this->equippedPlayer->setWeapon(this->weapons[3]);
	} else if (weaponId == CRIMP_STAFF_CODE) {
		this->equippedPlayer->setWeapon(this->weapons[4]);
	} else if (weaponId == SIMPLE_BOW_CODE) {
		this->equippedPlayer->setWeapon(this->weapons[6]);
	} else if (weaponId == COMPOUND_BOW_CODE) { 
		this->equippedPlayer->setWeapon(this->weapons[5]);
	} else {
		this->equippedPlayer->setWeapon(NULL);
	}
}

void Player::set_helmet(int helmetId) {
	if (helmetId == HOOD_CODE) {
		this->equippedPlayer->setHelmet(this->helmets[0]);
	} else if (helmetId == IRON_HELMET_CODE) {
		this->equippedPlayer->setHelmet(this->helmets[1]);
	} else if (helmetId == MAGIC_HAT_CODE) {
		this->equippedPlayer->setHelmet(this->helmets[2]);
	} else {
		this->equippedPlayer->setHelmet(NULL);
	}
}

void Player::set_armor(int armorId) {
	if (armorId == LEATHER_ARMOR_CODE) {
		this->playerPicture->set_clothes(this->clothes[1]);
	} else if (armorId == PLATE_ARMOR_CODE) {
		this->playerPicture->set_clothes(this->clothes[2]);
	} else if (armorId == BLUE_ROBE_CODE) { 
		this->playerPicture->set_clothes(this->clothes[3]);
	} else {
		this->playerPicture->set_clothes(this->clothes[0]);
	}
}

void Player::set_shield(int shieldId) {
	if (shieldId == TURTLE_SHIELD_CODE) {
		this->equippedPlayer->setShield(this->shields[1]);
	} else if (shieldId == IRON_SHIELD_CODE){
		this->equippedPlayer->setShield(this->shields[0]);
	} else {
		this->equippedPlayer->setShield(NULL);
	}
}

MessageToServer Player::handleEvent( SDL_Event& e, SDL_Rect &camera ) {

	std::vector<int16_t> args;
	int event_id = 1;
	int x = 0;
	int y = 0;
	if( e.type == SDL_KEYDOWN ) {
		switch( e.key.keysym.sym ) {
            case SDLK_UP: 
				event_id = PROTOCOL_MOVE_TOP;
				this->getPosArgs(args);
				break;

            case SDLK_DOWN:
				event_id = PROTOCOL_MOVE_DOWN;
				this->getPosArgs(args);
				break;

            case SDLK_LEFT:
				event_id = PROTOCOL_MOVE_LEFT;
				this->getPosArgs(args); 
				break;

            case SDLK_RIGHT:
				event_id = PROTOCOL_MOVE_RIGHT;
				this->getPosArgs(args);
				break;

			case SDLK_a:
				event_id = PROTOCOL_TAKE_ITEM;
				break;

			case SDLK_d:
				event_id = PROTOCOL_DEPOSIT;
				break;

			case SDLK_s:
				event_id = PROTOCOL_WITHDRAW;
				break;

			case SDLK_f:
				event_id = PROTOCOL_RESURRECT;
				break;

			case SDLK_c:
				event_id = PROTOCOL_HEAL;
				break;

			case SDLK_z:
				event_id = PROTOCOL_MEDITATION;
				break;			
        }

	} else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
		event_id = PROTOCOL_MOVE_STOP;

	} 
	else if ( e.type == SDL_MOUSEBUTTONDOWN) {
		SDL_GetMouseState( &x, &y ); 
		event_id = PROTOCOL_ATTACK;
		otherPosX = x + camera.x; 
		otherPosY = y + camera.y;
		args.push_back(otherPosX);
		args.push_back(otherPosY);
	}

	MessageToServer msg(
		event_id,
		this->id,
		args
	);

	return std::move(msg);
}


MessageToServer Player::handleEquipEvent(int &itemId) {
	std::vector<int16_t> args;
	args.push_back(itemId);
	std::cout << "EQUIPANDO ITEM ID: " << itemId << std::endl;
	int16_t event_id = this->getEventId(itemId, args);
	MessageToServer msg(
		event_id, 
		this->id,
		args
	);
	return std::move(msg);
}


MessageToServer Player::handleDropEvent(int &itemId) {
	std::vector<int16_t> args;
	args.push_back(itemId);
	this->itemId = itemId;
	MessageToServer msg(
		PROTOCOL_DROP_ITEM, 
		this->id,
		args
	);
	return std::move(msg);
}



void Player::getPosArgs(std::vector<int16_t> &args) {
	args.push_back(bodyPosX);
	args.push_back(bodyPosY);
}



uint8_t Player::getDroppedItem() const {
	return this->itemId;
}

uint8_t Player::getEquippedPotion() const {
	return this->potionId;
}


int16_t Player::getEventId(int &itemId, std::vector<int16_t> &args) {
	if (itemId < HOOD_CODE) {
		armorId = itemId;
		return PROTOCOL_EQUIP_ARMOR;
	} else if ((itemId >= HOOD_CODE) && (itemId < TURTLE_SHIELD_CODE)) {
		helmetId = itemId;	
		return PROTOCOL_EQUIP_HELMET;
	} else if ((itemId >= TURTLE_SHIELD_CODE) && (itemId < SWORD_CODE)) {
		shieldId = itemId;
		return PROTOCOL_EQUIP_SHIELD;
	} else if ((itemId >= SWORD_CODE) && (itemId < LIFE_POTION_CODE)) { 
		weaponId = itemId;
		return PROTOCOL_EQUIP_WEAPON;
	} else {
		potionId = itemId;
		return PROTOCOL_EQUIP_POTION;
	}
}



uint16_t Player::getId() const {
	return this->id;
}


Player::~Player() {
	for (unsigned int i = 0; i < clothes.size(); ++i) 
		delete clothes[i];

	for (unsigned int i = 0; i < weapons.size(); ++i) 
		delete weapons[i];

	for (unsigned int i = 0; i < helmets.size(); ++i) 
		delete helmets[i];

	for (unsigned int i = 0; i < shields.size(); ++i) 
		delete shields[i];

	delete playerPicture;
	delete equippedPlayer;

	if (ghost != NULL)
		delete ghost;
}

