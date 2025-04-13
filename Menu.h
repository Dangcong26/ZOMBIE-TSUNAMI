//#ifndef MAIN_MENU_H_
//#define MAIN_MENU_H_
//
//#include "Base.h"
//#include "include.h"
//
//class MainMenu {
//public:
//    enum MenuState {
//        MENU_NONE,    // Chưa chọn
//        MENU_PLAY,    // Nhấn Play
//        MENU_QUIT     // Nhấn Quit
//    };
//
//    MainMenu();
//    ~MainMenu();
//
//    // Khởi tạo menu: tải background và các nút
//    bool Init(SDL_Renderer* screen);
//
//    // Xử lý sự kiện chuột
//    void HandleInput(SDL_Event& e);
//
//    // Vẽ menu lên màn hình
//    void Render(SDL_Renderer* screen);
//
//    // Lấy trạng thái menu
//    MenuState GetState() const { return state_; }
//
//private:
//    Base background_; // Background của menu
//    Base play_button_normal_; // Nút Play (bình thường)
//    Base play_button_hover_;  // Nút Play (hover)
//    Base quit_button_normal_; // Nút Quit (bình thường)
//    Base quit_button_hover_;  // Nút Quit (hover)
//
//    bool is_play_hovered_; // Trạng thái hover của nút Play
//    bool is_quit_hovered_; // Trạng thái hover của nút Quit
//    MenuState state_;      // Trạng thái menu hiện tại
//};
//
//#endif