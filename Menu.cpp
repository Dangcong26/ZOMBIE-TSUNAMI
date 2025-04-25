#include "Menu.h"

Menu::Menu() : selected_item_(0) {
    selected_color_ = { 255, 0, 0, 255 };
    normal_color_ = { 255, 255, 255, 255 };
    font_ = nullptr;
    memset(item_rects_, 0, sizeof(item_rects_));

    for (int i = 0; i < TOTAL_ITEMS; i++) {
        menu_items_[i].SetText("");
    }
}

Menu::~Menu() {
    if (font_) {
        TTF_CloseFont(font_);
        font_ = nullptr;
    }
}

bool Menu::LoadFont(const std::string& font_path, int font_size) {
    font_ = TTF_OpenFont(font_path.c_str(), font_size);
    if (font_ == nullptr) {
        SDL_Log("Failed to load font: %s", TTF_GetError());
        return false;
    }
    return true;
}

bool Menu::LoadBackground(const std::string& bg_path, SDL_Renderer* screen) {
    bool success = background_.LoadImg(bg_path.c_str(), screen);
    if (!success) {
        SDL_Log("Failed to load menu background: %s", SDL_GetError());
        return false;
    }
    return true;
}

void Menu::Render(SDL_Renderer* screen) {
    SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
    SDL_RenderClear(screen);

    if (background_.GetObject() != nullptr) {
        background_.Render(screen, nullptr);
    }
    else {
        SDL_Log("Warning: Menu background not loaded, using black background");
    }

    if (menu_items_[START_GAME].GetText().empty()) {
        menu_items_[START_GAME].SetText("START GAME");
        menu_items_[QUIT].SetText("QUIT");
    }

    int start_y = (SCREEN_HEIGHT - (TOTAL_ITEMS * 100)) / 2;

    for (int i = 0; i < TOTAL_ITEMS; i++) {
        if (i == selected_item_) {
            menu_items_[i].SetColor(selected_color_.r, selected_color_.g, selected_color_.b);
        }
        else {
            menu_items_[i].SetColor(normal_color_.r, normal_color_.g, normal_color_.b);
        }

        if (!menu_items_[i].LoadFromRenderText(font_, screen)) {
            SDL_Log("Failed to render menu item %d: %s", i, TTF_GetError());
            continue;
        }

        int item_width = menu_items_[i].GetWidth();
        int item_height = menu_items_[i].GetHeight();

        int x_pos = (SCREEN_WIDTH - item_width) / 2;
        int y_pos = start_y + (i * 100);

        item_rects_[i] = { x_pos, y_pos, item_width, item_height };

        menu_items_[i].RenderText(screen, x_pos, y_pos, nullptr, 0.0, nullptr, SDL_FLIP_NONE);
    }
}

bool Menu::IsMouseClickOnItem(int itemIndex, int mouseX, int mouseY) {
    return (mouseX >= item_rects_[itemIndex].x &&
        mouseX <= item_rects_[itemIndex].x + item_rects_[itemIndex].w &&
        mouseY >= item_rects_[itemIndex].y &&
        mouseY <= item_rects_[itemIndex].y + item_rects_[itemIndex].h);
}

void Menu::HandleEvent(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        if (e.button.button == SDL_BUTTON_LEFT) {
            int mouseX = e.button.x;
            int mouseY = e.button.y;

            for (int i = 0; i < TOTAL_ITEMS; i++) {
                if (IsMouseClickOnItem(i, mouseX, mouseY)) {
                    selected_item_ = i;
                    break;
                }
            }
        }
    }
    else if (e.type == SDL_MOUSEMOTION) {
        int mouseX = e.motion.x;
        int mouseY = e.motion.y;

        for (int i = 0; i < TOTAL_ITEMS; i++) {
            if (IsMouseClickOnItem(i, mouseX, mouseY)) {
                selected_item_ = i;
                break;
            }
        }
    }
}