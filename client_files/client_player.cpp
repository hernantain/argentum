
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
	this->armorId = 0;
	this->weaponId = 0;
	this->shieldId = 0;
	this->helmetId = 0;
}


    
void Player::set_camera(SDL_Rect &camera) {

	camera.x = ( this->bodyPosX +  18 ) - camera.w / 2;
	camera.y = ( this->bodyPosY + 18 ) - camera.h / 2;

	//Keep the camera in bounds
	if( camera.x < 0 )
		camera.x = 0;
	
	if( camera.y < 0 ) 
		camera.y = 0;
	
	if( camera.x > 3200 - camera.w )
		camera.x = 3200 - camera.w;
	
	if( camera.y > 3200 - camera.h )
		camera.y = 3200 - camera.h; 
}

void Player::set_position(int16_t newBodyPosX, int16_t newBodyPosY, int orientation) {
	// std::unique_lock<std::mutex> lock(this->m);
	this->orientation = orientation;
	this->bodyPosX = newBodyPosX;
	this->bodyPosY = newBodyPosY;
	this->headPosX = newBodyPosX+this->headOffsetX;
	this->headPosY = newBodyPosY+this->headOffsetY;
}


// void Player::update_frames() {
// 	if (this->frame / 5 >= 5)
// 		this->frame = 0;
// }



void Player::render(SDL_Rect &camera, int &it) {
	// std::unique_lock<std::mutex> lock(this->m);
	equippedPlayer->render(
		bodyPosX - camera.x, 
		bodyPosY - camera.y, 
		headPosX - camera.x, 
		headPosY - camera.y, 
		gRenderer, 
		this->orientation, 
		it
	);
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
	if (weaponId == 9) {
		this->equippedPlayer->setWeapon(this->weapons[0]);
	} else if (weaponId == 10) {
		this->equippedPlayer->setWeapon(this->weapons[1]);
	} else if (weaponId == 11) {
		this->equippedPlayer->setWeapon(this->weapons[2]);
	} else if (weaponId == 13) {
		this->equippedPlayer->setWeapon(this->weapons[7]);
	} else if (weaponId == 14) {
		this->equippedPlayer->setWeapon(this->weapons[3]);
	} else if (weaponId == 15) {
		this->equippedPlayer->setWeapon(this->weapons[6]);
	} else if (weaponId == 17) { 
		this->equippedPlayer->setWeapon(this->weapons[5]);
	} else {
		this->equippedPlayer->setWeapon(this->weapons[4]);
	}
}

void Player::set_helmet(int helmetId) {
	if (helmetId == 4) {
		this->equippedPlayer->setHelmet(this->helmets[0]);
	} else if (helmetId == 5) {
		this->equippedPlayer->setHelmet(this->helmets[1]);
	} else {
		this->equippedPlayer->setHelmet(this->helmets[2]);
	}
}

void Player::set_armor(int armorId) {
	if (armorId == 1) {
		this->playerPicture->set_clothes(this->clothes[1]);
	} else if (armorId == 2) {
		this->playerPicture->set_clothes(this->clothes[2]);
	}  else { 
		this->playerPicture->set_clothes(this->clothes[3]);
	}
}

void Player::set_shield(int shieldId) {
	if (shieldId == 7) {
		this->equippedPlayer->setShield(this->shields[1]);
	} else {
		this->equippedPlayer->setShield(this->shields[0]);
	} 
}


ProtocolMessage Player::handleEvent( SDL_Event& e, SDL_Rect &camera ) {
	//If a key was pressed
	// std::unique_lock<std::mutex> lock(m);
	int event_id = 1;
	int x, y;
	if( e.type == SDL_KEYDOWN ) {
		switch( e.key.keysym.sym ) {
            case SDLK_UP: 
				event_id = 10;
				break;

            case SDLK_DOWN:
				event_id = 13;
				break;

            case SDLK_LEFT:
				event_id = 12; 
				break;

            case SDLK_RIGHT:
				event_id = 11;
				break;

			/* A CAMBIAR */
			case SDLK_m:
				event_id = 4;
				armorId = this->clothes[1]->get_id();
				break;

			case SDLK_n:
				event_id = 4;
				armorId = this->clothes[2]->get_id();
				break;

			case SDLK_v:
				event_id = 4;
				armorId = this->clothes[3]->get_id(); 
				break;

			case SDLK_b:
				this->playerPicture->set_clothes(this->clothes[0]);
				break;

			case SDLK_h:
				event_id = 3;
				helmetId = this->helmets[0]->get_id();
				break;

			case SDLK_j:
				event_id = 3;
				helmetId = this->helmets[1]->get_id();
				break;

			case SDLK_k:
				event_id = 3;
				helmetId = this->helmets[2]->get_id();
				break;

			case SDLK_l:
				this->equippedPlayer->setHelmet(NULL);
				break;

			case SDLK_q:
				event_id = 6;
				shieldId = this->shields[0]->get_id();
				break;

			case SDLK_w:
				event_id = 6;
				shieldId = this->shields[1]->get_id();
				break;

			case SDLK_e:
				event_id = 5;
				weaponId = this->weapons[7]->get_id();
				break;

			case SDLK_r:
				event_id = 5;
				weaponId = this->weapons[6]->get_id(); // SIMPLE BOW
				break;

			case SDLK_t:
				event_id = 5;
				weaponId = this->weapons[5]->get_id(); // COMPOUND BOW
				break;

			case SDLK_u:
				event_id = 5;
				weaponId = this->weapons[0]->get_id(); // SOWRD
				break;

			case SDLK_y:
				event_id = 5;
				weaponId = this->weapons[1]->get_id(); // AXE
				break;

			case SDLK_i:
				event_id = 5;
				weaponId = this->weapons[2]->get_id(); // HAMMER
				break;

			case SDLK_o:
				event_id = 5;
				weaponId = this->weapons[3]->get_id(); // BACULO ENGARZADO
				break;

			case SDLK_p:
				event_id = 5;
				weaponId = this->weapons[4]->get_id(); // BACULO NUDOSO
				break;

			case SDLK_z:
				event_id = 7;
				break;			
        }

	} else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
		event_id = 9;

	} else if ( e.type == SDL_MOUSEBUTTONDOWN) {
		SDL_GetMouseState( &x, &y ); 
		event_id = 2;
		otherPosX = x + camera.x; 
		otherPosY = y + camera.y;
		std::cout << "CLICK EN: " << x + camera.x << " Y EN: " << y + camera.y << std::endl; 
	}

	ProtocolCharacter character(
		this->id,
		this->bodyPosX, 
		this->bodyPosY,
		this->orientation,
		this->otherPosX,
		this->otherPosY,
		this->helmetId,
		this->armorId,
		this->weaponId,
		this->shieldId
	);
	ProtocolMessage msg(event_id, this->id, character);
	return std::move(msg);
}


uint16_t Player::getId() const {
	return this->id;
}
