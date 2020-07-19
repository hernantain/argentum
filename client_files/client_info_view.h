#ifndef _CLIENT_INFO_VIEW
#define _CLIENT_INFO_VIEW

#include <mutex>
#include <stdint.h>
#include <vector>
#include <SDL2/SDL.h>

#include "client_item.h"
#include "client_item_viewer.h"
#include "client_text.h"

#define ICON_SIZE 32
#define BAR_HEIGHT 10 

class InfoView {

    std::mutex m;
    std::vector<Item*> items;

    SDL_Rect &infoPanel;
    ItemViewer &itemViewer;
    TextLabel argentumLabel;
    TextLabel lifeLabel; 
    TextLabel manaLabel;
    TextLabel expLabel;
    
    SDL_Renderer* gRenderer;

    SDL_Rect currentLifeRect, maxLifeRect;
    SDL_Rect currentManaRect, maxManaRect;
    SDL_Rect currentExpRect, maxExpRect;

    SDL_Color manaColor, lifeColor, expColor, bgdColor; 

    int16_t currentMana, maxMana;
    int16_t currentLife, maxLife;
    int16_t currentExp, maxExp;

    void render_life();
    void render_mana();
    void render_experience();
    void render_items();

    bool click_within_bounds(Item* item, int &x, int &y);
    bool x_within_bounds(Item* item, int &x);
    bool y_within_bounds(Item* item, int &y);
    void adjust_items();
    void cleanItems(unsigned int i);

    public:
        InfoView(SDL_Renderer* gRenderer, SDL_Rect &infoPanel, ItemViewer &itemViewer);

        void set_mana(int16_t currentMana, int16_t maxMana);
        void set_life(int16_t currentLife, int16_t maxLife);
        void set_experience(int16_t currentExp, int16_t maxExperience);

        void add_item(Item* item);

        int handle_click(int &x, int &y);
        int handleDrop(int &x, int &y);

        void render();

        void adjust();

        void clear_items();

};


#endif
