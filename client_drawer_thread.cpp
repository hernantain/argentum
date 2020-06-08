

#include "client_drawer_thread.h"



ClientDrawerThread::ClientDrawerThread(
    Character &character,
    SDL_Renderer* gRenderer) : character(character), gRenderer(gRenderer) {}


void ClientDrawerThread::run() {
    bool running = true;

    while (running) {
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		
		character.render(this->gRenderer);

		//Update screen
		SDL_RenderPresent( this->gRenderer );

		character.update_frames();
    }
}