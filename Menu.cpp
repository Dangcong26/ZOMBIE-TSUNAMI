//#include "Menu.h"
//
//MainMenu::MainMenu() {
//    is_play_hovered_ = false;
//    is_quit_hovered_ = false;
//    state_ = MENU_NONE;
//}
//
//MainMenu::~MainMenu() {
//    background_.Free();
//    play_button_normal_.Free();
//    play_button_hover_.Free();
//    quit_button_normal_.Free();
//    quit_button_hover_.Free();
//}
//
//bool MainMenu::Init(SDL_Renderer* screen) {
//    // Tải background
//    bool success = background_.LoadImg("ZOMBIE TSUNAMI/menu_background.png", screen);
//    if (!success) return false;
//
//    // Tải sprite cho nút Play
//    success &= play_button_normal_.LoadImg("ZOMBIE TSUNAMI/play_normal.png", screen);
//    success &= play_button_hover_.LoadImg("ZOMBIE TSUNAMI/play_hover.png", screen);
//    if (!success) return false;
//    play_button_normal_.SetRect(540, 300); // Sử dụng setter
//    play_button_hover_.SetRect(540, 300);  // Đồng bộ vị trí
//
//    // Tải sprite cho nút Quit
//    success &= quit_button_normal_.LoadImg("ZOMBIE TSUNAMI/quit_normal.png", screen);
//    success &= quit_button_hover_.LoadImg("ZOMBIE TSUNAMI/quit_hover.png", screen);
//    if (!success) return false;
//    quit_button_normal_.SetRect(540, 400); // Sử dụng setter
//    quit_button_hover_.SetRect(540, 400);  // Đồng bộ vị trí
//
//    return true;
//}
//
//void MainMenu::HandleInput(SDL_Event& e) {
//    if (e.type == SDL_MOUSEMOTION) {
//        int x, y;
//        SDL_GetMouseState(&x, &y);
//
//        // Kiểm tra hover nút Play
//        SDL_Rect play_rect = play_button_normal_.GetRect();
//        is_play_hovered_ = (x >= play_rect.x &&
//            x <= play_rect.x + play_rect.w &&
//            y >= play_rect.y &&
//            y <= play_rect.y + play_rect.h);
//
//        // Kiểm tra hover nút Quit
//        SDL_Rect quit_rect = quit_button_normal_.GetRect();
//        is_quit_hovered_ = (x >= quit_rect.x &&
//            x <= quit_rect.x + quit_rect.w &&
//            y >= quit_rect.y &&
//            y <= quit_rect.y + quit_rect.h);
//    }
//    else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
//        int x, y;
//        SDL_GetMouseState(&x, &y);
//
//        // Kiểm tra nhấn nút Play
//        SDL_Rect play_rect = play_button_normal_.GetRect();
//        if (x >= play_rect.x &&
//            x <= play_rect.x + play_rect.w &&
//            y >= play_rect.y &&
//            y <= play_rect.y + play_rect.h) {
//            state_ = MENU_PLAY;
//        }
//        // Kiểm tra nhấn nút Quit
//        SDL_Rect quit_rect = quit_button_normal_.GetRect();
//        if (x >= quit_rect.x &&
//            x <= quit_rect.x + quit_rect.w &&
//            y >= quit_rect.y &&
//            y <= quit_rect.y + quit_rect.h) {
//            state_ = MENU_QUIT;
//        }
//    }
//}
//
//void MainMenu::Render(SDL_Renderer* screen) {
//    // Vẽ background
//    background_.Render(screen, nullptr);
//
//    // Vẽ nút Play
//    if (is_play_hovered_) {
//        play_button_hover_.Render(screen, nullptr);
//    }
//    else {
//        play_button_normal_.Render(screen, nullptr);
//    }
//
//    // Vẽ nút Quit
//    if (is_quit_hovered_) {
//        quit_button_hover_.Render(screen, nullptr);
//    }
//    else {
//        quit_button_normal_.Render(screen, nullptr);
//    }
//}