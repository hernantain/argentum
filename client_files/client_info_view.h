#ifndef _CLIENT_INFO_VIEW
#define _CLIENT_INFO_VIEW

#include <mutex>
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

    int currentMana, maxMana;
    int currentLife, maxLife;
    int currentExp, maxExp;

    void render_life();
    void render_mana();
    void render_experience();

    public:
        InfoView(SDL_Renderer* gRenderer, SDL_Rect &infoPanel);

        void set_mana(int currentMana, int maxMana);

        void set_life(int currentLife, int maxLife);

        void set_experience(int currentExp, int maxExperience);

        void render();

        void adjust();

};


#endif
