#ifndef _MAIN_PROGRAM
#define _MAIN_PROGRAM

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

#include "client_texture.h"

#include "../common_sockets.h"

class MainProgram {
	
	SDL_Window *gWindow;
	SDL_Renderer *gRenderer;
	bool running;
	Socket skt;

	bool init();

	public:
		explicit MainProgram();

		void run();

		~MainProgram();

};

#endif