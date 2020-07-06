
#include <iostream>

#include "client_info_view.h"


void InfoView::render_life() {
    SDL_SetRenderDrawColor(gRenderer, bgdColor.r, bgdColor.g, bgdColor.b, bgdColor.a);
    SDL_RenderFillRect(gRenderer, &maxLifeRect);

    SDL_SetRenderDrawColor(gRenderer, lifeColor.r, lifeColor.g, lifeColor.b, lifeColor.a);
    float pct = float(this->currentLife) / this->maxLife;
    currentLifeRect.w = maxLifeRect.w * pct;

    SDL_RenderFillRect(gRenderer, &currentLifeRect);
}


void InfoView::render_mana() {
    SDL_SetRenderDrawColor(gRenderer, bgdColor.r, bgdColor.g, bgdColor.b, bgdColor.a);
    SDL_RenderFillRect(gRenderer, &maxManaRect);

    SDL_SetRenderDrawColor(gRenderer, manaColor.r, manaColor.g, manaColor.b, manaColor.a);
    float pct = float(this->currentMana) / this->maxMana;
    currentManaRect.w = maxManaRect.w * pct;
    SDL_RenderFillRect(gRenderer, &currentManaRect);
}



InfoView::InfoView(
    SDL_Renderer* gRenderer, 
    SDL_Rect &infoPanel) : infoPanel(infoPanel) {
    
    this->lifeColor =  {36, 255, 240, 0xFF};
    this->manaColor =  {255, 175, 36, 0xFF};
    this->bgdColor = {20, 11, 11, 0xFF};

    // this->currentLife = 100;
    // this->maxLife = 100;
    // this->currentMana = 100;
    // this->maxMana = 100;

    this->adjust();

    this->gRenderer = gRenderer;
}


void InfoView::set_mana(int currentMana, int maxMana) {
    std::cout << "SETTING LIFE: " << currentMana << " AND MAX: " << maxMana << std::endl;
    this->currentMana = currentMana;
    this->maxMana = maxMana;
}


void InfoView::set_life(int currentLife, int maxLife) {
    std::cout << "SETTING LIFE: " << currentLife << " AND MAX: " << maxLife << std::endl;
    this->currentLife = currentLife;
    this->maxLife = maxLife;
}



void InfoView::render() {
    this->render_life();
    this->render_mana();
}


void InfoView::adjust() {
    
    int paddedX = infoPanel.w / 8;
    int paddedW = infoPanel.w - (2*paddedX);

    // LIFE
    currentLifeRect.x = paddedX;
    currentLifeRect.y = infoPanel.h / 2; 
    currentLifeRect.w = paddedW;
    currentLifeRect.h = BAR_HEIGHT;

    maxLifeRect.x = paddedX;
    maxLifeRect.y = infoPanel.h / 2; 
    maxLifeRect.w = paddedW;
    maxLifeRect.h = BAR_HEIGHT;

    // MANA
    currentManaRect.x = paddedX;
    currentManaRect.y = (currentLifeRect.y + infoPanel.h) / 2;
    currentManaRect.w = paddedW;
    currentManaRect.h = BAR_HEIGHT;

    maxManaRect.x = paddedX;
    maxManaRect.y = (maxLifeRect.y + infoPanel.h) / 2;
    maxManaRect.w = paddedW;
    maxManaRect.h = BAR_HEIGHT;
}