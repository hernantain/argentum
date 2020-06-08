#ifndef _CLIENT_DRAWER_THREAD
#define _CLIENT_DRAWER_THREAD

#include "client_character.h"
#include "common_thread.h"

class ClientDrawerThread : public Thread {
    Character &character;
    SDL_Renderer* gRenderer;
    public:
        ClientDrawerThread(Character &character, SDL_Renderer* gRenderer);

        virtual void run() override;

};




#endif
