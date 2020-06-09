
#include "client_drawer_thread.h"



ClientDrawerThread::ClientDrawerThread(
    Character &character,
    SDL_Renderer* gRenderer) : character(character), 
                                gRenderer(gRenderer),
                                running(true) {}



void ClientDrawerThread::run() {

    while (this->running) {
        
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer );

		character.render(this->gRenderer);

		SDL_RenderPresent( this->gRenderer ); //Update screen

		character.update_frames();
    }
}
