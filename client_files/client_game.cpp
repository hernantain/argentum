#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <chrono>

#include "client_game.h"
#include "client_sender_thread.h"
#include "client_receiver_thread.h"
#include "client_player.h"
#include "client_map.h"
#include "client_npc.h"


#include "../common_files/common_protocol_message.h"
#include "../common_files/common_queue.h"
#include "../common_files/common_sockets.h"
#include "../common_files/common_mapinfo.h"

#include <msgpack.hpp>


Game::Game(
	int16_t player_race, 
	int16_t player_class) :  gRenderer(NULL), 
							 running(true), 
							 player_race(player_race),
							 player_class(player_class) {
	if( !this->init() ) {
		printf( "Failed to initialize!\n" );
		exit(1); // LANZAR EXCEPCION?
	}

	inventory.x =  3 * (this->window.getWidth() / 4);
	inventory.y = 0;
	inventory.w = this->window.getWidth() / 4;
	inventory.h = this->window.getHeight();

	main.x = 0;
	main.y = 0;
	main.w = 3 * (this->window.getWidth() / 4);
	main.h = this->window.getHeight();
	// SDL_RenderSetViewport( gRenderer, &main );

	camera.x = main.x;
	camera.y = main.y;
	camera.w = main.w;
	camera.h = camera.h;
}


Map Game::loadMap() {
	MapInfo mapInfo;

	msgpack::unpacker pac;
	skt >> pac;
	msgpack::object_handle oh;
	pac.next(oh);
	msgpack::object obj = oh.get();
	obj.convert(mapInfo);
	
	Map map(gRenderer);
    map.load(mapInfo);

	return std::move(map);
}


ClientWorld Game::loadWorld(InfoView &infoView) {
	ProtocolCharacter character(this->player_id, this->player_race, this->player_class);
	ProtocolMessage msg(65, this->player_id, std::move(character)); // 65 para crear

	msgpack::sbuffer buffer;
	msgpack::packer<msgpack::sbuffer> pk(&buffer);
	pk.pack(msg);
	skt << buffer;	

    ProtocolMessage rec_msg;
    msgpack::unpacker pac;
    skt >> pac;
    msgpack::object_handle oh;
    pac.next(oh);
    msgpack::object obj = oh.get();
    obj.convert(rec_msg);
    
	ClientWorld clientWorld(gRenderer);

	for (unsigned int i = 0; i < rec_msg.characters.size(); ++i) {
		if (rec_msg.characters[i].id == this->player_id) {
			infoView.set_life(rec_msg.characters[i].life, rec_msg.characters[i].max_life);
			infoView.set_mana(rec_msg.characters[i].mana, rec_msg.characters[i].max_mana);
		}
		clientWorld.add_player(rec_msg.characters[i]);
	}

	for (unsigned int i = 0; i < rec_msg.npcs.size(); ++i) 
		clientWorld.add_npc(rec_msg.npcs[i]);

	return std::move(clientWorld);
}



void Game::run() {
	
	skt.connect_to("localhost", "8080");
	skt >> this->player_id;
	Map map = this->loadMap();

	InfoView infoView(this->gRenderer, inventory);
	ClientWorld world = this->loadWorld(infoView);

	Thread* sender = new SenderThread(skt, queue);
	sender->start();

	Player* player = world.players[this->player_id];

	Thread* receiver = new ClientReceiverThread(skt, world, camera, infoView, player_id);
	receiver->start();

	int it = 0;
	
	// auto rate = std::chrono::duration<double, std::milli>(float(1000)/60);
	// auto t_start = std::chrono::high_resolution_clock::now();
	
	SDL_Event e;
	// Event handler
	while(this->running) {	
		while( SDL_PollEvent( &e ) != 0 ) {
			if( e.type == SDL_QUIT ) {
				this->running = false;
				skt.close_socket();

			} else if (e.type == SDL_WINDOWEVENT) {
				this->window.handleEvent(e);
				this->adjust_camera(infoView);

			} else if (e.type == SDL_MOUSEMOTION) {
				continue;

			} else {
				ProtocolMessage msg = player->handleEvent(e, camera);
				queue.push(msg);	
			}
		}

		SDL_RenderSetViewport( gRenderer, &inventory );
		SDL_SetRenderDrawColor(gRenderer, 17, 5, 92, 1);
		SDL_RenderClear( gRenderer );
		infoView.render();

		SDL_RenderSetViewport( gRenderer, &main );
		map.renderFirstLayer(camera);
		world.render(this->player_id, camera, it);
		map.renderSecondLayer(camera);
		
		SDL_RenderPresent( this->gRenderer ); //Update screen
				
		// auto t_end = std::chrono::high_resolution_clock::now();
		// auto rest = rate - (t_end - t_start);
		// std::cout << std::chrono::duration<double, std::milli>((t_end - t_start)).count() << " ms - " << rate.count() << std::endl;
		// if (rest.count() < 0) {
		// 	auto behind = std::chrono::duration<double, std::milli>(-rest);
		// 	auto mod = std::chrono::duration<double, std::milli>(fmod(float(behind.count()), float(rate.count())));
		// 	auto lost = std::chrono::duration<double, std::milli>(behind - mod);
		// 	// it += floor(lost / rate);
		// }
		// //std:: cout << int(rest.count()) << std::endl;
		// //std::this_thread::sleep_for(std::chrono::milliseconds(int(rest.count())));
		// // t_start = t_start. + rate.count();
		// // t_start = std::chrono::high_resolution_clock::now();
		it++;
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


void Game::adjust_camera(InfoView &infoView) {

	inventory.x =  3 * (this->window.getWidth() / 4);
	inventory.w = 1 * (this->window.getWidth() / 4);
	inventory.h = this->window.getHeight();
	SDL_RenderSetViewport( gRenderer, &inventory );
	
	this->main.w = 3 * (this->window.getWidth() / 4);
	this->main.h = this->window.getHeight();
	SDL_RenderSetViewport( gRenderer, &main );
	
	camera.w = main.w;
	camera.h = main.h;

	infoView.adjust();
}




Game::~Game() {
	SDL_DestroyRenderer(this->gRenderer);
	this->gRenderer = NULL;

	IMG_Quit(); //Quit SDL subsystems
	SDL_Quit();
}
