
#include "client_sound_manager.h"



SoundManager::SoundManager() {
    if ((!loadMusic()) || (!loadSounds())) 
        exit(1);
        
    this->currentItem = 0;
    Mix_VolumeMusic(20);
}


bool SoundManager::loadMusic() {
    this->gMusic = Mix_LoadMUS("media/sound/music2.wav");
	if(gMusic == NULL) {
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

    return true;
}


bool SoundManager::loadSounds() {
    swordSound = Mix_LoadWAV("media/sound/sword.wav");
	if(swordSound == NULL) {
		printf("Failed to load sword sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

    axeSound = Mix_LoadWAV("media/sound/axe.wav");
	if(axeSound == NULL) {
		printf("Failed to load axe sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

    hammerSound = Mix_LoadWAV("media/sound/hammer.wav");
	if(hammerSound == NULL) {
		printf("Failed to load hammer sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

    explosionSound = Mix_LoadWAV("media/sound/explosion.wav");
	if(explosionSound == NULL) {
		printf("Failed to load explosion sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

    arrowSound = Mix_LoadWAV("media/sound/arrow.wav");
	if(arrowSound == NULL) {
		printf("Failed to load arrow sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}

    return true;
}



void SoundManager::play_pause_music() {
    std::unique_lock<std::mutex> lock(m);
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(gMusic, -1);
    } else {
        Mix_HaltMusic();
    }
}


void SoundManager::set_sound(int item) {
    std::unique_lock<std::mutex> lock(m);
    this->currentItem = item;
}


void SoundManager::play_sound() {
    std::unique_lock<std::mutex> lock(m);
    switch (this->currentItem) {
        case 0:
            return;

        case SWORD_CODE:
            Mix_PlayChannel(-1, swordSound, 0);
            break;

        case AXE_CODE:
            Mix_PlayChannel(-1, axeSound, 0);
            break;

        case HAMMER_CODE:
            Mix_PlayChannel(-1, hammerSound, 0);
            break;

        case CRIMP_STAFF_CODE:
            Mix_PlayChannel(-1, explosionSound, 0);
            break;

        case SIMPLE_BOW_CODE:
            Mix_PlayChannel(-1, arrowSound, 0);
            break;

        case COMPOUND_BOW_CODE:
            Mix_PlayChannel(-1, arrowSound, 0);
            break;
        }

    this->currentItem = 0;
}




SoundManager::~SoundManager() {
    Mix_FreeChunk(swordSound);
	Mix_FreeChunk(arrowSound);
	Mix_FreeChunk(axeSound);
	Mix_FreeChunk(explosionSound);
    Mix_FreeChunk(hammerSound);
	Mix_FreeMusic( gMusic );
}

