#ifndef _CLIENT_GAME
#define _CLIENT_GAME

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <stdint.h>

#include "client_texture.h"
#include "client_window.h"
#include "client_map.h"
#include "client_player.h"
#include "client_world.h"
#include "client_info_view.h"

#include "../common_files/common_sockets.h"
#include "../common_files/common_queue.h"
#include "../common_files/common_protocol_codes.h"


class Game {
	
	SDL_Renderer *gRenderer;
	bool running;
	uint8_t player_race, player_class;
	LWindow window;
	Queue queue;
	Socket skt;
	SDL_Rect main;
	SDL_Rect inventory;
	SDL_Rect camera;
	uint16_t player_id;


	bool init();
	void adjust_camera(InfoView &infoView);

	Map loadMap(); 
	ClientWorld loadWorld(InfoView &infoView, ItemViewer &itemViewer);


	public:
		Game(uint8_t player_race, uint8_t player_class);

		void run();

		~Game();

};

#endif
