#  ZOMBIE TSUNAMI


## Giới thiệu :

- Zombie Tsunami là một game 2D được phát triển bằng thư viện SDL2. Người chơi điều khiển một nhân vật zombie để vượt qua các chướng ngại vật, thu thập "brain", và tránh các mối nguy  hiểm như bom và đạn từ kẻ thù. Mục tiêu là sống sót càng lâu càng tốt và thu thập càng nhiều brain càng tốt.

- Dự án này được thực hiện để học hỏi và áp dụng kỹ năng lập trình C++ và sử dụng SDL2 để phát triển game.


## Tính năng :

- Điều khiển nhân vật zombie di chuyển (trái, phải) và nhảy (phím Space).

  <img src="ZOMBIE TSUNAMI/PLAYER.jpg" alt="ảnh nhân vật" width="100px">

- Ăn quái và não cùng fly bõ để thu thập thật nhiều não
  
  <img src="ZOMBIE TSUNAMI/threats.jpg" alt="ảnh nhân vật" width="100px">

  <img src="ZOMBIE TSUNAMI/4.png" alt="ảnh nhân vật" width="100px">

  <img src="ZOMBIE TSUNAMI/6.png" alt="ảnh nhân vật" width="100px">

- Tránh bom và đạn từ kẻ thù.
  
  <img src="Threats/Bullet.png" alt="đạn" width="100px">
  
  <img src="ZOMBIE TSUNAMI/5.png" alt="BOOM" width="100px">

- Hiệu ứng nổ khi va chạm với bom.

  <img src="ZOMBIE TSUNAMI/explosion.jpg" alt="hiệu ứng vụ nổ" width="100px">

- Menu chính với tùy chọn bắt đầu game hoặc thoát.
  
  <img src="ZOMBIE TSUNAMI/menudemo.png" alt="hiệu ứng vụ nổ" width="500px">
  
  <img src="ZOMBIE TSUNAMI/gamedemo.png" alt="hiệu ứng vụ nổ" width="500px">

- Âm thanh nền và hiệu ứng âm thanh (nhạc nền, tiếng cắn, tiếng nổ).

    
## Cách Chơi

- Dùng 2 nút mũi tên trên bàm phím để di chuyển
- Nhần SPACE để nhảy lên

## Mục tiêu:

  - Thu thập "brain" để tăng điểm số.

  - Tránh bom và đạn từ kẻ thù.

  - Nếu số "brain" giảm về 0 hoặc nhân vật rơi khỏi bản đồ, game sẽ kết thúc và quay lại menu.  


## Yêu cầu hệ thống

  - Hệ điều hành: Windows (có thể mở rộng sang Linux/Mac nếu cài đặt SDL2 phù hợp).


## Thư viện cần thiết:

  - SDL2

  - SDL2_image

  - SDL2_ttf

  - SDL2_mixer



## Công cụ phát triển:

  - Visual Studio (hoặc bất kỳ IDE nào hỗ trợ C++).

  - MinGW (nếu sử dụng trên Windows với Git Bash).

  - Git (để quản lý mã nguồn).


## Cấu trúc thư mục

  - ZOMBIE TSUNAMI/: Chứa hình ảnh nền và tài nguyên hình ảnh khác (Background1.png, menu_background.png).

  - Player/: Chứa hình ảnh của nhân vật (left.png, right.png, jump_left.png, jump_right.png).

  - Threats/: Chứa hình ảnh của kẻ thù và hiệu ứng nổ (threat_left.png, exp3.png).

  - gamemap/: Chứa file bản đồ (map.dat) và các ô tile (1.png, 2.png, ..., 6.png).

  - *.mp3, *.wav: Các file âm thanh (happy.mp3, bite.wav, explosion.wav).



## Danh sách file chính

  - MAIN.cpp: File chính, chứa vòng lặp game và logic chính.

  - Player.cpp, Player.h: Quản lý nhân vật người chơi.

  - Threats.cpp, Threats.h: Quản lý kẻ thù và đạn.

  - Menu.cpp, Menu.h: Quản lý menu chính.

  - Sound.h: Định nghĩa các biến âm thanh toàn cục.

  - gamemap/map.dat: File bản đồ game.


## Hướng dẫn cài đặt

1. Cài đặt SDL2 và các thư viện liên quan

    - Tải và cài đặt SDL2:

    - Tải SDL2 từ trang chính thức.

    - Tải các thư viện phụ: SDL2_image, SDL2_ttf, SDL2_mixer.

    - Cấu hình SDL2 trong Visual Studio:

    - Thêm các file .lib vào thư mục dự án hoặc cấu hình trong Visual Studio (Properties > Linker > Input).

    - Thêm đường dẫn đến các file header (.h) trong Properties > C/C++ > General > Additional Include Directories.

    - Sao chép các file .dll (như SDL2.dll, SDL2_image.dll, v.v.) vào thư mục chứa file thực thi của dự án.

2. Clone dự án từ Git

     - git clone https : <a href="//github.com/Dangcong26/ZOMBIE-TSUNAMI"><em>Link Github</em></a>
        
     - link video review : <a href="https://drive.google.com/file/d/1M5DMSVTZ1my-PWIF6DeZujWWYR4HfC38/view?usp=drive_link"><em>Link Video</em></a>

3. Biên dịch và chạy

     - Mở dự án trong Visual Studio bằng file SDL2GAME.vcxproj.

     - Build dự án (F5 hoặc Build > Build Solution).

     - Chạy game từ Visual Studio hoặc chạy file thực thi trong thư mục Debug/Release.

  ## Nguồn tham khảo
   - Youtube : <a href="https://www.youtube.com/c/Ph%C3%A1tTri%E1%BB%83nPh%E1%BA%A7nM%E1%BB%81m123AZ"><em>Link Github</em></a>
   - Grok AI : <a href="https://grok.com/?ref=aiartweekly"><em>Link Github</em></a>

## Đóng góp

 Nếu bạn muốn đóng góp cho dự án: Nếu bạn có ý tưởng hãy liên hệ với mình!
                                  Chân Thành Cảm Ơn !


## Tác giả

  Tên: Đặng Danh Công

  Email: dcong2k6@gmail.com

