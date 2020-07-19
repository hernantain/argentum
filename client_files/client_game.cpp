#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <chrono>

#include "client_game.h"
#include "client_sender_thread.h"
#include "client_receiver_thread.h"
#include "client_map.h"

#include "../common_files/common_message_to_server.h"
#include "../common_files/common_queue.h"
#include "../common_files/common_sockets.h"
#include "../common_files/common_mapinfo.h"

#include <msgpack.hpp>



Game::Game(
	uint8_t player_race, 
	uint8_t player_class) : gRenderer(NULL), 
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

	camera.x = main.x;
	camera.y = main.y;
	camera.w = main.w;
	camera.h = main.h;
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


ClientWorld Game::loadWorld(InfoView &infoView, ItemViewer &itemViewer) {
	std::vector<int16_t> args;
	args.push_back(this->player_race);
	args.push_back(this->player_class);
	MessageToServer msg(PROTOCOL_CREATE_CHARACTER, this->player_id, args);


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
    
	ClientWorld clientWorld(gRenderer, itemViewer);

	for (unsigned int i = 0; i < rec_msg.characters.size(); ++i) {
		if (rec_msg.characters[i].id == this->player_id) {
			infoView.set_life(rec_msg.characters[i].life, rec_msg.characters[i].max_life);
			infoView.set_mana(rec_msg.characters[i].mana, rec_msg.characters[i].max_mana);
			infoView.set_experience(rec_msg.characters[i].experience, rec_msg.characters[i].max_experience);
		}

		clientWorld.add_player(rec_msg.characters[i]);
	}

	for (unsigned int i = 0; i < rec_msg.npcs.size(); ++i) 
		clientWorld.add_npc(rec_msg.npcs[i]);

	for (unsigned int i = 0; i < rec_msg.items.size(); ++i)
		clientWorld.add_item(rec_msg.items[i]);

	return clientWorld;
}



void Game::run() {
	
	using namespace std::chrono;
	SoundManager sm;
	// sm.play_pause_music();

	skt.connect_to("localhost", "8080");
	skt >> this->player_id;
	Map map = this->loadMap();

	ItemViewer itemViewer(gRenderer);
	InfoView infoView(this->gRenderer, inventory, itemViewer);
	ClientWorld world = this->loadWorld(infoView, itemViewer);

	Thread* sender = new SenderThread(skt, queue);
	sender->start();

	Thread* receiver = new ClientReceiverThread(skt, world, camera, infoView, sm, player_id);
	receiver->start();

	int it = 0;	
	duration<int, std::milli> rate(17);
	system_clock::time_point t1 = system_clock::now();

	SDL_Event e;
	// Event handler
	while(this->running) {	
		while(SDL_PollEvent(&e) != 0) {
			if( e.type == SDL_QUIT ) {
				this->running = false;				
				std::vector<int16_t> args;
				args.push_back(0); // no va
				MessageToServer msg(PROTOCOL_LOG_OFF, this->player_id, args);
				queue.push(msg);
				break;

			} else if (e.type == SDL_WINDOWEVENT) {
				this->window.handleEvent(e);
				this->adjust_camera(infoView);
				continue;

			} else if ((e.type == SDL_MOUSEBUTTONDOWN) && (e.button.button == SDL_BUTTON_RIGHT)) {
				std::cout << "RIGHT CLICK" << std::endl;
				int x, y;
				SDL_GetMouseState( &x, &y ); 
				if (x > inventory.x) {
					int clickX = x - inventory.x;
					int itemId = infoView.handleDrop(clickX, y);
					if (itemId < 0)
						continue;

					MessageToServer msg = world.player_handle_drop_event(this->player_id, itemId);
					queue.push(msg);
				}
				continue;

			} else if (e.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState( &x, &y ); 
				if (x > inventory.x) {
					std::cout << "CLICK COMUN" << std::endl;
					int clickX = x - inventory.x;
					int itemId = infoView.handle_click(clickX, y); 
					std::cout << "Item ID ES:: " << itemId << std::endl;
					if (itemId < 0)
						continue;

					MessageToServer msg = world.player_handle_equip_event(this->player_id, itemId);
					queue.push(msg);
				}
				continue;

			} else if (e.type == SDL_MOUSEMOTION) {
				continue;

			} else if ((e.type == SDL_KEYDOWN) && (e.key.keysym.sym == SDLK_0)) {
				sm.play_pause_music();
				continue;
			}
			MessageToServer msg = world.player_handle_event(player_id, e, camera);
			queue.push(msg);
		}

		SDL_RenderSetViewport( gRenderer, &inventory );
		SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 1);
		SDL_RenderClear(gRenderer);
		infoView.render();

		SDL_RenderSetViewport(gRenderer, &main);
		map.renderFirstLayer(camera);
		world.render(this->player_id, camera, it);
		map.renderSecondLayer(camera);
		
		sm.play_sound();

		SDL_RenderPresent(this->gRenderer); 
				
		system_clock::time_point t2 = system_clock::now();
		duration<int,std::milli>rest = rate - duration_cast<std::chrono::duration<int,std::milli>>(t2 - t1);
		
		if (rest.count() < 0) {
			duration<int, std::milli> behind = duration<int, std::milli>(-rest);
			rest = rate - (behind % rate);
			duration<int, std::milli> lost = behind + rest;
			t1 += lost;
		 	it += (int) floor(lost.count() / rate.count());
		}
		std::this_thread::sleep_for(duration<int, std::milli>(rest.count()));
		t1 += rate;
		it++;
	}

	sender->join();
	delete sender;

	receiver->join();
	delete receiver;

	skt.close_socket();
}



bool Game::init() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		return false;
	} 
	
	if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		printf("Warning: Linear texture filtering not enabled!");
	} 

	if(!this->window.init()) {
		printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	} 
	
	this->gRenderer = this->window.createRenderer();
	if(this->gRenderer == NULL) {
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	} 

	SDL_SetRenderDrawColor( this->gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

	int imgFlags = IMG_INIT_PNG;
	if(!( IMG_Init( imgFlags ) & imgFlags)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	if(TTF_Init() == -1) {
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		return false;
	}

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
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

	TTF_Quit();
	IMG_Quit(); //Quit SDL subsystems
	SDL_Quit();
	Mix_Quit();	
}
