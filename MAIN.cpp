#include "include.h"
#include "Base.h"
#include "map.h"
#include "Player.h"
#include "Time-fps.h"
#include "Threats.h"
#include "Menu.h"
#include "Explosion.h"
#undef main

Base g_background;

bool InitData() {
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0) {
		return false;
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	g_window = SDL_CreateWindow("ZOMBIE TSUNAMI",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	if (g_window == NULL) {
		success = false;
	}
	else {
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL) success = false;
		else {
			SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags))
				success = false;
		}
	}
	return success;
}

bool LoadBackground() {
	bool ret = g_background.LoadImg("ZOMBIE TSUNAMI/Background1.png", g_screen);
	if (ret == false)
		return false;
	return true;
}

void close() {
	g_background.Free();

	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;

	SDL_DestroyWindow(g_window);
	g_window = NULL;

	IMG_Quit();
	SDL_Quit();
}

vector<Threats*> MakeThreatsList() {
	vector<Threats*> list_threats;
	/*Threats* dynamic_threats = new Threats[1];
	for (int i = 0; i < 1 ;i ++) {
		Threats* p_threat = (dynamic_threats + i);

		if (p_threat != NULL) {
			p_threat->LoadImg("Threats/threat_left.png", g_screen);
			p_threat->set_clips();
			p_threat->set_type_move(Threats::MOVE_IN_SPACE_THREAT);
			p_threat->set_x_pos(500 * i + 500);
			p_threat->set_y_pos(200);

			int pos1 = p_threat->get_x_pos() - 60;
			int pos2 = p_threat->get_x_pos() + 60;

			p_threat->SetAnimationPos(pos1, pos2);
			p_threat->set_input_left(1);

			Bullet* p_bullet = new Bullet();
			p_threat->InitBullet(p_bullet, g_screen);

			list_threats.push_back(p_threat);
		}
	}*/

	Threats* threats_objs = new Threats[10];
	for (int i = 0; i < 10; i++) {
		Threats* p_threat = (threats_objs + i);
		
		if (p_threat != NULL) {
			p_threat->LoadImg("stone.png", g_screen);
			p_threat->set_clips();
			p_threat->set_x_pos(1200 * i + 400);
			p_threat->set_y_pos(200);
			p_threat->set_type_move(Threats::STATIC_THREAT);
			p_threat->set_input_left(0);

			Bullet* p_bullet = new Bullet();
			p_threat->InitBullet(p_bullet, g_screen);

			list_threats.push_back(p_threat);
		}
	}
	return list_threats;
}
int main(int argc, char* argv[]) {

	Time fps_time;

	if (InitData() == false) {
		return -1;
	}

	if (LoadBackground() == false) {
		return -1;
	}

	GameMap game_map;
	game_map.LoadMap("gamemap/map.dat");
	game_map.LoadTiles(g_screen);

	Player p_player;
	p_player.LoadImg("Player//right.png", g_screen);
	p_player.set_clips();

	vector<Threats*> threats_list = MakeThreatsList();

	bool is_quit = false;

	while (!is_quit) {
		fps_time.start();
		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT) {
				is_quit = true;
			}

			p_player.HandleInputAction(g_event, g_screen);
		}

		SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);
		game_map.DrawMap(g_screen);
		Map map_data = game_map.getMap();

		p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
		p_player.DoPlayer(map_data);
		p_player.Show(g_screen);

		game_map.SetMap(map_data);
		game_map.DrawMap(g_screen);

		for (int i = 0; i < (int)threats_list.size(); i++) {
			Threats* p_threat = threats_list.at(i);
			if (p_threat != NULL) {
				p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
				p_threat->ImpMoveType(g_screen);
				p_threat->DoPlayer(map_data);
				p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat->Show(g_screen);

				SDL_Rect rect_player = p_player.GetRectFrame();
				bool bCol1 = false;
				vector<Bullet*> tBullet_list = p_threat->get_bullet_list();
				for (int jj = 0; jj < (int)tBullet_list.size(); jj++) {
					Bullet* pt_bullet = tBullet_list.at(jj);
					if (pt_bullet) {
						bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);
						if (bCol1) {
							p_threat->RemoveBullet(jj);
							break;
						}
					}
				}

				if (bCol1) {
					if (MessageBox(NULL, L"GAME OVER", L"Info" , MB_OK | MB_ICONSTOP) == IDOK) {
						p_threat->Free();
						close();
						SDL_Quit();
						return 0;
					}
				}

				SDL_Rect rect_threat = p_threat->GetRectFrame();
				bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);

				if (bCol2) {
					p_threat->Free();
					threats_list.erase(threats_list.begin() + i);
				}
			}
		}

		SDL_RenderPresent(g_screen);

		int real_imp_time = fps_time.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND; 

		if (real_imp_time < time_one_frame) {
			int delay_time = time_one_frame - real_imp_time;
			if (delay_time >= 0)
				SDL_Delay(delay_time);
		}
	}

	for (int i = 0; i < (int)threats_list.size(); i++) {
		Threats* p_threat = threats_list.at(i);
		if (p_threat) {
			p_threat->Free();
			p_threat = NULL;
		}
	}
	threats_list.clear();

	close();

	return 0;
}