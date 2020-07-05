
#include "client_hood.h"
#include "client_magic_hat.h"
#include "client_iron_helmet.h"
#include "client_axe.h"
#include "client_hammer.h"
#include "client_baculo_nudoso.h"
#include "client_baculo_engarzado.h"
#include "client_sword.h"
#include "client_player.h"
#include <iostream>

Player::Player(
    int bodyPosX, 
    int bodyPosY, 
    int headPosX, 
    int headPosY,
	int16_t id,
	SDL_Renderer* gRenderer) : Drawable(id, gRenderer),
                    bodyPosX(bodyPosX), 
                    bodyPosY(bodyPosY),
                    headPosX(headPosX),
                    headPosY(headPosY) {
	this->headOffsetX = headPosX - bodyPosX;
	this->headOffsetY = headPosY - bodyPosY;
}


int Player::getPosX() const {
	return this->bodyPosX;
}
    
int Player::getPosY() const {
	return this->bodyPosY;
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

void Player::set_position(int newBodyPosX, int newBodyPosY) {
	std::unique_lock<std::mutex> lock(this->m);
	this->bodyPosX = newBodyPosX;
	this->bodyPosY = newBodyPosY;
	this->headPosX = newBodyPosX+this->headOffsetX;
	this->headPosY = newBodyPosY+this->headOffsetY;
}


void Player::update_frames() {
	if (this->frame / 5 >= 5)
		this->frame = 0;
}



void Player::render(int camPosX, int camPosY) {
	std::unique_lock<std::mutex> lock(this->m);
	int bodyCenteredX = this->bodyPosX - camPosX;
	int bodyCenteredY = this->bodyPosY - camPosY;
	int headCenteredX = this->headPosX - camPosX;
	int headCenteredY = this->headPosY - camPosY;
	
	equippedPlayer->render(
		bodyCenteredX, 
		bodyCenteredY, 
		headCenteredX, 
		headCenteredY, 
		gRenderer, 
		this->orientation, 
		this->frame);

	this->frame++;
}



void Player::load_helmets() {
	Helmet* hood = new Hood(gRenderer);
	Helmet* ironHelmet = new IronHelmet(gRenderer);
	Helmet* magicHat = new MagicHat(gRenderer);
	this->helmets.push_back(hood);
	this->helmets.push_back(ironHelmet);
	this->helmets.push_back(magicHat);	
}


void Player::load_weapons() {
	Weapon* sword = new Sword(gRenderer);
	Axe* axe = new Axe(gRenderer);
	Hammer* hammer = new Hammer(gRenderer);
	BaculoEngarzado* baculoEngarzado = new BaculoEngarzado(gRenderer);
	BaculoNudoso* baculoNudoso = new BaculoNudoso(gRenderer);
	this->weapons.push_back(sword);
	this->weapons.push_back(axe);
	this->weapons.push_back(hammer);
	this->weapons.push_back(baculoNudoso);
	this->weapons.push_back(baculoEngarzado);
}

void Player::set_weapon(int weaponId) {
	if (weaponId == 9) {
		this->equippedPlayer->setWeapon(this->weapons[0]);
	} else if (weaponId == 10) {
		this->equippedPlayer->setWeapon(this->weapons[1]);
	} else if (weaponId == 11) {
		this->equippedPlayer->setWeapon(this->weapons[2]);
	} else if (weaponId == 14) {
		this->equippedPlayer->setWeapon(this->weapons[3]);
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
	} 
	// TODO: When blueRobe added
	// else { 
	// 	this->playerPicture->set_clothes(this->clothes[3]);
	// }
}

ProtocolMessage Player::handleEvent( SDL_Event& e, SDL_Rect &camera ) {
	//If a key was pressed
	int event_id = 1;
	int x, y;
	if( e.type == SDL_KEYDOWN ) {
		switch( e.key.keysym.sym ) { 						//Adjust velocity
            
            case SDLK_UP: 
				event_id = 10;
				orientation = UP;
				break;

            case SDLK_DOWN:
				event_id = 13;
				orientation = DOWN;
				break;

            case SDLK_LEFT:
				event_id = 12;
				orientation = LEFT; 
				break;

            case SDLK_RIGHT:
				event_id = 11;
				orientation = RIGHT;
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

			case SDLK_u:
				event_id = 5;
				weaponId = this->weapons[0]->get_id();
				break;

			case SDLK_y:
				event_id = 5;
				weaponId = this->weapons[1]->get_id();
				break;

			case SDLK_i:
				event_id = 5;
				weaponId = this->weapons[2]->get_id();
				break;

			case SDLK_o:
				event_id = 5;
				weaponId = this->weapons[3]->get_id();
				break;

			case SDLK_p:
				event_id = 5;
				weaponId = this->weapons[4]->get_id();
				break;

			case SDLK_z:
				event_id = 7;
				break;
			
        }

	} else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
		switch( e.key.keysym.sym ) { 						//Adjust velocity
			case SDLK_UP: 
				// velY += drawable_speed; 
				break;

            case SDLK_DOWN: 
				// velY -= drawable_speed; 
				break;

            case SDLK_LEFT: 
				// velX += drawable_speed; 
				break;

            case SDLK_RIGHT: 
				// velX -= drawable_speed; 
				break;

        }
		orientation = STANDING;

	} else if ( e.type == SDL_MOUSEBUTTONDOWN) {
		
		// CODIGO PARA CUANDO QUERRAMOS MANEJAR EL CLICK DEL PERSONAJE 
		SDL_GetMouseState( &x, &y ); 
		event_id = 2;
		otherPosX = x + camera.x; 
		otherPosY = y + camera.y;
		std::cout << "CLICK EN: " << x + camera.x << " Y EN: " << y + camera.y << std::endl; 
	}
	ProtocolCharacter character(
		this->id,
		1,
		1,
		this->bodyPosX, 
		this->bodyPosY,
		this->otherPosX,
		this->otherPosY,
		this->helmetId,
		this->armorId,
		this->weaponId
	);
	ProtocolMessage msg(event_id, this->id, std::move(character));
	return std::move(msg);
}


int16_t Player::getId() const {
	return this->id;
}
