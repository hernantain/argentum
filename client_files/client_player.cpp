
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
    int headPosY) : Drawable(10),
                    bodyPosX(bodyPosX), 
                    bodyPosY(bodyPosY),
                    headPosX(headPosX),
                    headPosY(headPosY) {}


int Player::getPosX() const {
	return this->bodyPosX;
}
    
int Player::getPosY() const {
	return this->bodyPosY;
}
    
void Player::set_camera(SDL_Rect &camera) {

	camera.x = ( this->bodyPosX +  18 ) - 640 / 2;
	camera.y = ( this->bodyPosY + 18 ) - 480 / 2;

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

void Player::set_position(int newBodyPosX, int newBodyPosY, int newHeadPosX, int newHeadPosY) {
	std::unique_lock<std::mutex> lock(this->m);
	this->bodyPosX = newBodyPosX;
	this->bodyPosY = newBodyPosY;
	this->headPosX = newHeadPosX;
	this->headPosY = newHeadPosY;
}


void Player::update_frames() {
	if (this->frame / 5 >= 5)
		this->frame = 0;
}



void Player::render(SDL_Renderer* gRenderer, int camPosX, int camPosY) {
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


void Player::load_helmets(SDL_Renderer* gRenderer) {
	Helmet* hood = new Hood(gRenderer);
	Helmet* ironHelmet = new IronHelmet(gRenderer);
	Helmet* magicHat = new MagicHat(gRenderer);
	this->helmets.push_back(hood);
	this->helmets.push_back(ironHelmet);
	this->helmets.push_back(magicHat);	
}


void Player::load_weapons(SDL_Renderer* gRenderer) {
	Weapon* sword = new Sword(gRenderer);
	Axe* axe = new Axe(gRenderer);
	Hammer* hammer = new Hammer(gRenderer);
	BaculoEngarzado* baculoEngarzado = new BaculoEngarzado(gRenderer);
	BaculoNudoso* baculoNudoso = new BaculoNudoso(gRenderer);
	this->weapons.push_back(sword);
	this->weapons.push_back(axe);
	this->weapons.push_back(hammer);
	this->weapons.push_back(baculoEngarzado);
	this->weapons.push_back(baculoNudoso);
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


ProtocolMessage Player::handleEvent( SDL_Event& e ) {
	//If a key was pressed
	int event_id = 1;
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ) {
		switch( e.key.keysym.sym ) { 						//Adjust velocity
            
            case SDLK_UP: 
				event_id = 1;
				velY -= drawable_speed; 
				orientation = UP;
				break;

            case SDLK_DOWN:
				event_id = 1;
				velY += drawable_speed;
				orientation = DOWN;
				break;

            case SDLK_LEFT:
				event_id = 1;
				velX -= drawable_speed;
				orientation = LEFT; 
				break;

            case SDLK_RIGHT:
				event_id = 1;
				velX += drawable_speed; 
				orientation = RIGHT;
				break;


			/* A CAMBIAR */
			case SDLK_m:
				this->playerPicture->set_clothes(this->clothes[1]);
				break;

			case SDLK_n:
				this->playerPicture->set_clothes(this->clothes[2]);
				break;

			case SDLK_b:
				this->playerPicture->set_clothes(this->clothes[0]);
				break;

			case SDLK_h:
				event_id = 3;
				// This line will be setted on the "onClick" event
				helmetId = this->helmets[0]->get_id();
				break;

			case SDLK_j:
				event_id = 3;
				// This line will be setted on the "onClick" event
				helmetId = this->helmets[1]->get_id();
				break;

			case SDLK_k:
				event_id = 3;
				// This line will be setted on the "onClick" event
				helmetId = this->helmets[2]->get_id();
				break;

			case SDLK_l:
				this->equippedPlayer->setHelmet(NULL);
				break;

			case SDLK_u:
				this->equippedPlayer->setWeapon(this->weapons[0]);
				break;

			case SDLK_y:
				this->equippedPlayer->setWeapon(this->weapons[1]);
				break;

			case SDLK_i:
				this->equippedPlayer->setWeapon(this->weapons[2]);
				break;

			case SDLK_o:
				this->equippedPlayer->setWeapon(this->weapons[3]);
				break;

			case SDLK_p:
				this->equippedPlayer->setWeapon(this->weapons[4]);
				break;
			
        }

	} else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
		switch( e.key.keysym.sym ) { 						//Adjust velocity
			case SDLK_UP: 
				velY += drawable_speed; 
				break;

            case SDLK_DOWN: 
				velY -= drawable_speed; 
				break;

            case SDLK_LEFT: 
				velX += drawable_speed; 
				break;

            case SDLK_RIGHT: 
				velX -= drawable_speed; 
				break;

        }
		orientation = STANDING;

	} else if ( e.type == SDL_MOUSEBUTTONDOWN) {
		
		// CODIGO PARA CUANDO QUERRAMOS MANEJAR EL CLICK DEL PERSONAJE
		// int x, y; 
		// SDL_GetMouseState( &x, &y ); 
		// std::cout << "CLICK EN: " << x << " Y EN: " << y << std::endl; 
	}

	ProtocolCharacter character(
		(int16_t) 1, 
		(int16_t) this->bodyPosX, 
		(int16_t) this->bodyPosY,
		(int16_t) this->headPosX, 
		(int16_t) this->headPosY, 
		(int16_t) this->velX, 
		(int16_t) this->velY,
		(int16_t) this->helmetId
	);
	ProtocolMessage msg(event_id, std::move(character));
	return std::move(msg);
}