
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


void InfoView::render_experience() {
    SDL_SetRenderDrawColor(gRenderer, bgdColor.r, bgdColor.g, bgdColor.b, bgdColor.a);
    SDL_RenderFillRect(gRenderer, &maxExpRect);

    SDL_SetRenderDrawColor(gRenderer, expColor.r, expColor.g, expColor.b, expColor.a);
    float pct = float(this->currentExp) / this->maxExp;
    currentExpRect.w = maxExpRect.w * pct;
    SDL_RenderFillRect(gRenderer, &currentExpRect);
}



InfoView::InfoView(
    SDL_Renderer* gRenderer, 
    SDL_Rect &infoPanel) : infoPanel(infoPanel) {
    
    this->manaColor =  {36, 255, 240, 0xFF};
    this->lifeColor =  {255, 175, 36, 0xFF};
    this->bgdColor = {20, 11, 11, 0xFF};
    this->expColor = {240, 255, 26, 0xFF};

    this->adjust();

    this->gRenderer = gRenderer;
}


void InfoView::set_mana(int16_t currentMana, int16_t maxMana) {
    std::unique_lock<std::mutex> lock(this->m);
    // std::cout << "SETTING MANA: " << currentMana << " AND MAX: " << maxMana << std::endl;
    this->currentMana = currentMana;
    this->maxMana = maxMana;
}


void InfoView::set_life(int16_t currentLife, int16_t maxLife) {
    std::unique_lock<std::mutex> lock(this->m);
    this->currentLife = currentLife;
    this->maxLife = maxLife;
}

void InfoView::set_experience(int16_t currentExp, int16_t maxExp) {
    std::unique_lock<std::mutex> lock(this->m);
    this->currentExp = currentExp;
    this->maxExp = maxExp;
}



void InfoView::render() {
    std::unique_lock<std::mutex> lock(this->m);
    this->render_life();
    this->render_mana();
    this->render_experience();
}


void InfoView::adjust() {
    std::unique_lock<std::mutex> lock(this->m);
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

    // EXP
    currentExpRect.x = paddedX;
    currentExpRect.y = (currentManaRect.y + infoPanel.h) / 2;
    currentExpRect.w = paddedW;
    currentExpRect.h = BAR_HEIGHT;

    maxExpRect.x = paddedX;
    maxExpRect.y = (maxManaRect.y + infoPanel.h) / 2;
    maxExpRect.w = paddedW;
    maxExpRect.h = BAR_HEIGHT;
}
