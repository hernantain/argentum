#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "client_game.h"
#include "client_sender_thread.h"
#include "client_receiver_thread.h"

#include "client_player.h"
#include "client_elf.h"
#include "client_human.h"
#include "client_dwarf.h"
#include "client_gnome.h"

#include "client_map.h"

#include "../common_protocol_message.h"
#include "../common_queue.h"
#include "../common_sockets.h"
#include "../common_mapinfo.h"

#include <msgpack.hpp>

#include <vector>

Game::Game() :  gRenderer(NULL), running(true) {
	if( !this->init() ) {
		printf( "Failed to initialize!\n" );
		exit(1); // LANZAR EXCEPCION?
	}

	camera.x = 0;
	camera.y = 0;
	camera.w = this->window.getWidth();
	camera.h = this->window.getHeight();
}


Map Game::loadMap() {
	std::cout << "POR CARGAR MAPA" << std::endl;

	MapInfo mapInfo;

	msgpack::unpacker pac;
	skt >> pac;
	msgpack::object_handle oh;
	pac.next(oh);
	msgpack::object obj = oh.get();
	obj.convert(mapInfo);
	
	Map map(gRenderer);
    map.load(mapInfo);

	std::cout << "MAPA CARGADO" << std::endl;
	return std::move(map);
}


ClientWorld Game::createPlayer() {
	ProtocolCharacter character(this->player_id, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0);
	ProtocolMessage msg(65, this->player_id, std::move(character)); // 65 para crear
	

	std::cout << "POR MANDAR CHARACTER" << std::endl;
	msgpack::sbuffer buffer;
	msgpack::packer<msgpack::sbuffer> pk(&buffer);
	pk.pack(msg);
	skt(buffer);

	std::cout << "Corriendo" << std::endl;
    ProtocolMessage rec_msg;
    msgpack::unpacker pac;
    skt >> pac;
    msgpack::object_handle oh;
    pac.next(oh);
    msgpack::object obj = oh.get();
    obj.convert(rec_msg);
    
	ClientWorld clientWorld;

	Player* player;
	for (unsigned int i = 0; i < rec_msg.characters.size(); ++i) {
		std::cout << "i: " << i << " - REC MESSAGE RACE: " << rec_msg.characters[i].id_race << std::endl;
		if (rec_msg.characters[i].id_race == 1) {
			player = new Human(gRenderer, this->player_id);
			clientWorld.players.insert(std::pair<int16_t, Player*> (rec_msg.id_player, player));
		} else if (rec_msg.characters[i].id_race == 2) {
			player = new Elf(gRenderer, this->player_id);
			clientWorld.players.insert(std::pair<int16_t, Player*> (rec_msg.id_player, player));
		} else if (rec_msg.characters[i].id_race == 3) {
			player = new Dwarf(gRenderer, this->player_id);
			clientWorld.players.insert(std::pair<int16_t, Player*> (rec_msg.id_player, player));
		} else {
			player = new Gnome(gRenderer, this->player_id);
			clientWorld.players.insert(std::pair<int16_t, Player*> (rec_msg.id_player, player));
		}
 	}

	return clientWorld;
}



void Game::run() {
		
	skt.connect_to("localhost", "8080");

	skt >> this->player_id;
	std::cout << "PLAYER ID: " << this->player_id << std::endl;

	Map map = this->loadMap();
	ClientWorld world = this->createPlayer();


	Thread* sender = new SenderThread(skt, queue);
	sender->start();

	// Elf player(gRenderer);	
	Player* player = world.players[this->player_id];


	// Recibe la respuesta del server y modifica o no en el modelo
	Thread* receiver = new ClientReceiverThread(skt, player, camera);
	receiver->start();


	//Event handler
	SDL_Event e;
	while(this->running) {
		
		while( SDL_PollEvent( &e ) != 0 ) {
			if( e.type == SDL_QUIT ) {
				this->running = false;
				skt.close_socket();
			} else if (e.type == SDL_WINDOWEVENT) {
				this->window.handleEvent(e);
				this->adjust_camera(this->window.getWidth(), this->window.getHeight());

			} else {
				
				ProtocolMessage msg = player->handleEvent( e );
				queue.push(msg);	
			}
		}


		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		map.renderFirstLayer(camera);
		player->render(this->gRenderer, camera.x, camera.y);
		map.renderSecondLayer(camera);
		
		SDL_RenderPresent( this->gRenderer ); //Update screen
		player->update_frames();
		
		// sleep
	}
}



bool Game::init() {

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		return false;
	} 
	
	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
		printf( "Warning: Linear texture filtering not enabled!" );
	} 


	if( !this->window.init() ) {
		printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	} 
	

	this->gRenderer = this->window.createRenderer();
	if( this->gRenderer == NULL ) {
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	} 
	//Initialize renderer color
	SDL_SetRenderDrawColor( this->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}

	return true;
}


void Game::adjust_camera(int width, int height) {
	this->camera.w = width;
	this->camera.h = height;
}




Game::~Game() {

	SDL_DestroyRenderer( this->gRenderer );
	this->gRenderer = NULL;

	IMG_Quit(); //Quit SDL subsystems
	SDL_Quit();
}
