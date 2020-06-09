#ifndef _CLIENT_DRAWER_THREAD
#define _CLIENT_DRAWER_THREAD

#include <atomic>

#include "client_character.h"
#include "common_thread.h"

class ClientDrawerThread : public Thread {
    Character &character;
    SDL_Renderer* gRenderer;
    std::atomic<bool> running;
    public:
        ClientDrawerThread(Character &character, SDL_Renderer* gRenderer);

        virtual void run() override;

};




#endif
