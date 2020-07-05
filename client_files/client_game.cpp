#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "client_game.h"
#include "client_sender_thread.h"
#include "client_receiver_thread.h"
#include "client_player.h"
#include "client_map.h"
#include "client_npc.h"

#include "../common_protocol_message.h"
#include "../common_queue.h"
#include "../common_sockets.h"
#include "../common_mapinfo.h"

#include <msgpack.hpp>


Game::Game() :  gRenderer(NULL), running(true) {
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


ClientWorld Game::loadWorld() {
	ProtocolCharacter character(this->player_id, 2, 1);
	ProtocolMessage msg(65, this->player_id, std::move(character)); // 65 para crear

	msgpack::sbuffer buffer;
	msgpack::packer<msgpack::sbuffer> pk(&buffer);
	pk.pack(msg);
	skt(buffer);	

    ProtocolMessage rec_msg;
    msgpack::unpacker pac;
    skt >> pac;
    msgpack::object_handle oh;
    pac.next(oh);
    msgpack::object obj = oh.get();
    obj.convert(rec_msg);
    
	ClientWorld clientWorld(gRenderer);

	for (unsigned int i = 0; i < rec_msg.characters.size(); ++i) 
		clientWorld.add_player(rec_msg.characters[i]);

	for (unsigned int i = 0; i < rec_msg.npcs.size(); ++i) 
		clientWorld.add_npc(rec_msg.npcs[i]);

	return std::move(clientWorld);
}



void Game::run() {
	
	skt.connect_to("localhost", "8080");
	skt >> this->player_id;
	Map map = this->loadMap();

	ClientWorld world = this->loadWorld();

	Thread* sender = new SenderThread(skt, queue);
	sender->start();

	Player* player = world.players[this->player_id];

	Thread* receiver = new ClientReceiverThread(skt, world, camera, player_id);
	receiver->start();

	// float rate = float( 1000 * float( 1.0 ) / float( 60.0) ) ;

	int it = 0;
	SDL_Event e;
	// auto rate = std::chrono::duration<double>(float(1.0/60));
	// auto t_start = std::chrono::high_resolution_clock::now();
	// SDL_RenderSetViewport(this->gRenderer, NULL);
	
	// Event handler
	while(this->running) {	
		while( SDL_PollEvent( &e ) != 0 ) {
			if( e.type == SDL_QUIT ) {
				this->running = false;
				skt.close_socket();

			} else if (e.type == SDL_WINDOWEVENT) {
				this->window.handleEvent(e);
				this->adjust_camera();

			} else if (e.type == SDL_MOUSEMOTION) {
				continue;

			} else {
				ProtocolMessage msg = player->handleEvent(e, camera);
				queue.push(msg);	
			}
		}

		// SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		SDL_RenderSetViewport( gRenderer, &inventory );
		SDL_SetRenderDrawColor(gRenderer, 17, 5, 92, 1);

		SDL_RenderSetViewport( gRenderer, &main );

		map.renderFirstLayer(camera);
		world.render(this->player_id, camera, it);
		map.renderSecondLayer(camera);
		
		// SDL_RenderSetViewport( gRenderer, &inventory );
		// SDL_SetRenderDrawColor(gRenderer, 225, 150, 100, 1);

		// SDL_RenderCopy(this->gRenderer, NULL, NULL, NULL);
				
		SDL_RenderPresent( this->gRenderer ); //Update screen
		
		
		
		// auto t_end = std::chrono::high_resolution_clock::now();
		// auto rest = rate - (t_end - t_start);
		// std::cout << std::chrono::duration<double>(t_end - t_start).count() << " ms - " << rate.count() << std::endl;
		
		// if (rest.count() < 0) {
		// 	std::cout << "Es negativo" << std::endl;
		// 	auto behind = std::chrono::duration<double>(-rest);
		// 	std::cout << std::chrono::duration<double>(behind - (behind % rate)).count()  << std::endl;
		// }
	
		// t_start = std::chrono::high_resolution_clock::now();
		
		it++;
		// player->update_frames();
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


void Game::adjust_camera() {

	inventory.x =  3 * (this->window.getWidth() / 4);
	inventory.w = 1 * (this->window.getWidth() / 4);
	inventory.h = this->window.getHeight();
	SDL_RenderSetViewport( gRenderer, &inventory );
	
	this->main.w = 3 * (this->window.getWidth() / 4);
	this->main.h = this->window.getHeight();
	SDL_RenderSetViewport( gRenderer, &main );
	
	camera.w = main.w;
	camera.h = main.h;
}




Game::~Game() {

	SDL_DestroyRenderer( this->gRenderer );
	this->gRenderer = NULL;

	IMG_Quit(); //Quit SDL subsystems
	SDL_Quit();
}
