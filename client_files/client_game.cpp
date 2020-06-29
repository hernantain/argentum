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


void Game::run() {
		
	skt.connect_to("localhost", "8080");
	Map map = this->loadMap();


	Thread* sender = new SenderThread(skt, queue);
	sender->start();

	Dwarf player(gRenderer);	


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
				
				ProtocolMessage msg = player.handleEvent( e );
				queue.push(msg);	
			}
		}


		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		map.renderFirstLayer(camera);
		player.render(this->gRenderer, camera.x, camera.y);
		map.renderSecondLayer(camera);
		
		SDL_RenderPresent( this->gRenderer ); //Update screen
		player.update_frames();
		
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
