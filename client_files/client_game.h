#ifndef _CLIENT_GAME
#define _CLIENT_GAME

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

#include "client_texture.h"
#include "client_window.h"
#include "client_map.h"

#include "../common_sockets.h"
#include "../common_queue.h"

class Game {
	
	LWindow window;
	SDL_Renderer *gRenderer;
	Queue queue;
	bool running;
	Socket skt;

	bool init();

	Map loadMap(); 
	public:
		explicit Game();

		void run();

		~Game();

};

#endif
