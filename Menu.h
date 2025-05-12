#ifndef MENU_H_
#define MENU_H_

#include "include.h"
#include "Text.h"
#include "Base.h"

class Menu {
public:
    enum MenuItem {
        START_GAME,
        QUIT,
        TOTAL_ITEMS
    };

    Menu();
    ~Menu();

    bool LoadFont(const std::string& font_path, int font_size);
    bool LoadBackground(const std::string& bg_path, SDL_Renderer* screen);
    void Render(SDL_Renderer* screen);
    void HandleEvent(SDL_Event& e);
    int GetSelectedItem() const { return selected_item_; }
    void Reset() { selected_item_ = 0; };

    bool IsMouseClickOnItem(int itemIndex, int mouseX, int mouseY);

private:
    TTF_Font* font_;
    Text menu_items_[TOTAL_ITEMS];
    Base background_;
    int selected_item_;
    SDL_Color selected_color_;
    SDL_Color normal_color_;

    SDL_Rect item_rects_[TOTAL_ITEMS];
};

#endif 