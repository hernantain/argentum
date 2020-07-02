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

#include "../common_sockets.h"
#include "../common_queue.h"


class Game {
	
	SDL_Renderer *gRenderer;
	bool running;
	LWindow window;
	Queue queue;
	Socket skt;
	SDL_Rect camera;
	uint16_t player_id;


	bool init();
	void adjust_camera(int width, int height);

	Map loadMap(); 
	ClientWorld createPlayer();


	public:
		explicit Game();

		void run();

		~Game();

};

#endif
