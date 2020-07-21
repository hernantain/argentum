#ifndef _CLIENT_SOUND_MANAGER
#define _CLIENT_SOUND_MANAGER

#include <mutex>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../common_files/common_protocol_codes.h"

class SoundManager {

    std::mutex m;
    Mix_Music* gMusic;
    Mix_Chunk* swordSound;
    Mix_Chunk* axeSound;
    Mix_Chunk* hammerSound;
    Mix_Chunk* explosionSound;
    Mix_Chunk* arrowSound; 
    int currentItem;
    bool loadMusic();
    bool loadSounds();
    public:
        SoundManager();

        void play_pause_music();

        void play_sound();

        void set_sound(int item);

        ~SoundManager();


};



#endif
