
#include <iostream>

#include "client_info_view.h"


InfoView::InfoView(
    SDL_Renderer* gRenderer, 
    SDL_Rect &infoPanel,
    ItemViewer &itemViewer) : infoPanel(infoPanel), 
                              itemViewer(itemViewer), 
                              argentumLabel(gRenderer, "Argentum", 30),
                              lifeLabel(gRenderer, "Vida", 30),
                              manaLabel(gRenderer, "Mana", 30),
                              expLabel(gRenderer, "Experiencia", 30) {
                            //   currLifeLabel(gRenderer, "0", 20),
                            //   maxLifeLabel(gRenderer, "0", 20) {
    
    this->manaColor =  {36, 255, 240, 0xFF};
    this->lifeColor =  {255, 175, 36, 0xFF};
    this->bgdColor = {20, 11, 11, 0xFF};
    this->expColor = {240, 255, 26, 0xFF};

    this->currentMana = 0;
    this->maxMana = 0;
    this->currentExp = 0;
    this->maxExp = 0;
    this->currentLife = 0;
    this->maxLife = 0;

    this->adjust();

    this->gRenderer = gRenderer;
}


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
    float pct = this->currentMana == 0 ? 0 : float(this->currentMana) / this->maxMana;
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


void InfoView::adjust_items() {
    int paddedX = infoPanel.w / 8;
    int paddedW = infoPanel.w - paddedX;
    int y = 100;
    for (unsigned int i = 0; i < items.size(); ++i) {
        if (paddedX + ICON_SIZE >= paddedW) {
            y += 50;
            paddedX = infoPanel.w / 8;
        }
        
        this->items[i]->set_posX(paddedX);
        this->items[i]->set_posY(y);
        paddedX += 55;
    }
}


void InfoView::render_items() {
    for (unsigned int i = 0; i < items.size(); ++i) {
        uint8_t itemId = items[i]->get_id();
        int16_t posX = items[i]->get_posX();
        int16_t posY = items[i]->get_posY();

        LTexture* item = this->itemViewer.get_item_icon(itemId);
        item->render(posX, posY, gRenderer);
    }
}


int InfoView::handle_click(int &x, int &y) {
    for (unsigned int i = 0; i < items.size(); ++i) {
        if (click_within_bounds(items[i], x, y)) 
            return items[i]->get_id();
    }
    return -1;
}


int InfoView::handleDrop(int &x, int &y) {
    for (unsigned int i = 0; i < items.size(); ++i) {
        if (click_within_bounds(items[i], x, y)) {
            int id = items[i]->get_id();
            // this->cleanItems(i);
            return id;
        }
    }
    return -1;
}


void InfoView::dropItem(uint8_t &itemId) {
    for (unsigned int i = 0; i < items.size(); ++i) {
        uint8_t id = items[i]->get_id();
        if (id == itemId) 
            this->cleanItems(i);
    }
}


void InfoView::cleanItems(unsigned int i) {
    std::vector<Item*> tmp;
    for (unsigned int j = 0; j < items.size(); ++j) {
        if (j == i) {
            delete items[j];
            continue;
        }

        tmp.push_back(items[j]);
    }
    items.swap(tmp);
}



bool InfoView::click_within_bounds(Item* item, int &x, int &y) {
    return (x_within_bounds(item, x) && y_within_bounds(item, y));
}


bool InfoView::x_within_bounds(Item* item, int &x) {
    return (x > item->get_posX()) && (x < item->get_posX() + ICON_SIZE);
}

bool InfoView::y_within_bounds(Item* item, int &y) {
    return ((y > item->get_posY()) && (y < item->get_posY() + ICON_SIZE));
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
    // this->currLifeLabel.set_new_label(std::to_string(this->currentLife));
    // this->maxLifeLabel.set_new_label(std::to_string(this->maxLife));
}


void InfoView::set_experience(int16_t currentExp, int16_t maxExp) {
    std::unique_lock<std::mutex> lock(this->m);
    this->currentExp = currentExp;
    this->maxExp = maxExp;
}


void InfoView::add_item(Item* item) {
    std::unique_lock<std::mutex> lock(this->m);
    for (unsigned int i = 0; i < items.size(); ++i) {
        if (items[i]->get_id() == item->get_id()) {
            this->items[i]->add_amount();
            delete item;
        }
    }
    this->items.push_back(item);
    this->adjust_items();
}



void InfoView::render() {
    std::unique_lock<std::mutex> lock(this->m);
    this->render_life();
    this->render_mana();
    this->render_experience();
    this->render_items();
    argentumLabel.render((infoPanel.w - argentumLabel.getWidth()) / 2, 30);
    lifeLabel.render((infoPanel.w - lifeLabel.getWidth()) / 2, currentLifeRect.y - 40);
    // currLifeLabel.render(maxLifeRect.x, maxLifeRect.y - 30);
    // maxLifeLabel.    render(maxLifeRect.x + maxLifeRect.w, maxLifeRect.y - 30);
    manaLabel.render((infoPanel.w - manaLabel.getWidth()) / 2, currentManaRect.y - 40);
    expLabel.render((infoPanel.w - expLabel.getWidth()) / 2, currentExpRect.y - 40);
}


void InfoView::adjust() {
    std::unique_lock<std::mutex> lock(this->m);
    int paddedX = infoPanel.w / 8;
    int paddedW = infoPanel.w - (2*paddedX);

    // LIFE
    currentLifeRect = {paddedX, infoPanel.h / 2, paddedW, BAR_HEIGHT};
    maxLifeRect = {paddedX, infoPanel.h / 2, paddedW, BAR_HEIGHT};

    // MANA
    currentManaRect = {paddedX, (currentLifeRect.y + infoPanel.h) / 2, paddedW, BAR_HEIGHT};
    maxManaRect = {paddedX, (maxLifeRect.y + infoPanel.h) / 2, paddedW, BAR_HEIGHT};

    // EXP
    currentExpRect = {paddedX, (currentManaRect.y + infoPanel.h) / 2, paddedW, BAR_HEIGHT};
    maxExpRect = {paddedX, (maxManaRect.y + infoPanel.h) / 2, paddedW, BAR_HEIGHT};

    this->adjust_items();
}

void InfoView::clear_items() {
    std::unique_lock<std::mutex> lock(this->m);
    for (unsigned int i = 0; i < items.size(); ++i) 
        delete items[i];

    items.clear();
}
