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
    TextLabel lifeLabel, manaLabel, expLabel; 
    TextLabel currLifeLabel, maxLifeLabel;
    TextLabel currManaLabel, maxManaLabel;
    TextLabel currExpLabel, maxExpLabel;
    TextLabel goldLabel, goldNumberLabel;
    TextLabel levelLabel, levelNumberLabel;
    
    SDL_Renderer* gRenderer;

    SDL_Rect currentLifeRect, maxLifeRect;
    SDL_Rect currentManaRect, maxManaRect;
    SDL_Rect currentExpRect, maxExpRect;

    SDL_Color manaColor, lifeColor, expColor, bgdColor; 

    int16_t currentMana, maxMana;
    int16_t currentLife, maxLife;
    int16_t currentExp, maxExp;
    int16_t currentGold;
    int16_t currentLevel;


    void render_life();
    void render_mana();
    void render_experience();
    void render_life_bar();
    void render_mana_bar();
    void render_experience_bar();
    void render_items();
    void render_gold_level();

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
        void set_gold(int16_t gold);
        void set_level(int16_t level);

        void add_item(Item* item);

        int handle_click(int &x, int &y);
        int handleDrop(int &x, int &y);
        void dropItem(uint8_t &itemId);

        void render();

        void adjust();

        void clear_items();
};


#endif
