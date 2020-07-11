#ifndef _CLIENT_INFO_VIEW
#define _CLIENT_INFO_VIEW

#include <mutex>
#include <stdint.h>
#include <SDL2/SDL.h>

#define BAR_HEIGHT 10 

class InfoView {

    std::mutex m;
    
    SDL_Rect &infoPanel;    
    SDL_Renderer* gRenderer;

    SDL_Rect currentLifeRect;
    SDL_Rect maxLifeRect;
    
    SDL_Rect currentManaRect;
    SDL_Rect maxManaRect;

    SDL_Rect currentExpRect;
    SDL_Rect maxExpRect;

    SDL_Color manaColor; 
    SDL_Color lifeColor;
    SDL_Color expColor;
    SDL_Color bgdColor;

    int16_t currentMana, maxMana;
    int16_t currentLife, maxLife;
    int16_t currentExp, maxExp;

    void render_life();
    void render_mana();
    void render_experience();

    public:
        InfoView(SDL_Renderer* gRenderer, SDL_Rect &infoPanel);

        void set_mana(int16_t currentMana, int16_t maxMana);

        void set_life(int16_t currentLife, int16_t maxLife);

        void set_experience(int16_t currentExp, int16_t maxExperience);

        void render();

        void adjust();

};


#endif
