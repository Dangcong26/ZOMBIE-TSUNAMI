#include "Player.h"

Player::Player() {
	frame_ = 1;
	x_pos_ = 0;
	y_pos_ = 0;
	x_val_ = 0;
	y_val_ = 0;
	width_frame_ = 0;
	height_frame_ = 0;
	status_ = -1;
	input_type_.left_ = 0;
	input_type_.right_ = 0;
	input_type_.up_ = 0;
	input_type_.down_ = 0;
	on_ground_ = false;
	map_x_ = 0;
	map_y_ = 0;
	brain = 5;
	is_exploding_ = false; 
	explosion_frame_ = 0;
}

Player::~Player() {

}

bool Player::LoadImg(string path, SDL_Renderer* screen) {
	bool ret = Base::LoadImg(path, screen);
	
	if (ret == true) {
		width_frame_ = rect_.w / 10;
		height_frame_ = rect_.h;
	}
	return ret;
}

void Player::InitExplosion(SDL_Renderer* screen) {
	// Khởi tạo đối tượng vụ nổ từ Explosion.h
	bool ret = explosion_.LoadImg("Threats/exp3.png", screen); // Đường dẫn tới hình ảnh vụ nổ
	if (ret) {
		explosion_.set_clip(); // Thiết lập các khung hình của vụ nổ
	}
}

SDL_Rect Player::GetRectFrame() {
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame_;
	rect.h = height_frame_;

	return rect;
}

void Player::set_clips() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		for (int i = 0; i < 8; i++) {
			frame_clip_[i].x = i * width_frame_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
}


void Player::Show(SDL_Renderer* des) {
	if (on_ground_ == true) {
		if (status_ == WALK_LEFT) {
			LoadImg("Player//left.png", des);
		}
		else {
			LoadImg("Player//right.png", des);
		}
	}

	if (input_type_.left_ == 1 || input_type_.right_ == 1) {
		frame_++;
	}
	else {
		frame_ = 0;
	}

	if (frame_ >= 8) {
		frame_ = 0;
	}

	rect_.x = x_pos_ - map_x_;
	rect_.y = y_pos_ - map_y_;

	SDL_Rect* current_clip = &frame_clip_[frame_];

	SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_ };

	SDL_RenderCopy(des, p_object_, current_clip, &renderQuad);
}

void Player::HandleInputAction(SDL_Event events, SDL_Renderer* screen) {
	if (events.type == SDL_KEYDOWN) {
		switch (events.key.keysym.sym) {
		case SDLK_RIGHT: {
			status_ = WALK_RIGHT;
			input_type_.left_ = 0;
			input_type_.right_ = 1;
			if (on_ground_ == true) {
				LoadImg("Player/right.png", screen);
			}
			else {
				LoadImg("Player/jump_right.png", screen);
			}
		}
					   break;
		case SDLK_LEFT: {
			status_ = WALK_LEFT;
			input_type_.right_ = 0;
			input_type_.left_ = 1;
			if (on_ground_ == true) {
				LoadImg("Player/left.png", screen);
			}
			else {
				LoadImg("Player/jump_left.png", screen);
			}
		}
					  break;
		default:
			break;
		}
	}
	else if(events.type == SDL_KEYUP){
		switch (events.key.keysym.sym) {
		case SDLK_RIGHT: {
			input_type_.right_ = 0;
		}
					   break;
		case SDLK_LEFT: {
			input_type_.left_ = 0;
		}
					  break;
		default:
			break;
		}
	}

	if (events.type == SDL_MOUSEBUTTONDOWN) {
		if (events.button.button == SDL_BUTTON_RIGHT) {
			input_type_.jump_ = 1;
		}
	}
}

void Player::DoPlayer(Map& map_data) {
	x_val_ = 0;
	y_val_ += 0.8;

	if (y_val_ >= MAX_FAIL_SPEED) {
		y_val_ = MAX_FAIL_SPEED;
	}

	if(input_type_.left_ == 1) {
		x_val_ -= PLAYER_SPEED;
	}
	else if (input_type_.right_ == 1) {
		x_val_ += PLAYER_SPEED;
	}

	if (input_type_.jump_ == 1) {
		if (on_ground_ == true) {
			y_val_ = - PLAYER_JUMP_VAL;
		}
		on_ground_ = false;
		input_type_.jump_ = 0;
	}

	CheckToMap(map_data);
	//Handlefalling();
	CentreEntityOnMap(map_data);
}

void Player::CheckToMap(Map& map_data) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	//chieu ngang

	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (x_val_ > 0) { // di chuyen ve ben phai
			int val1 = map_data.tile[y1][x2];
			int val2 = map_data.tile[y2][x2];

			if (val1 == STATE_BRAIN || val2 == STATE_BRAIN) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;
				IncreateBrain();
			}else if (val1 == STATE_BOOM || val2 == STATE_BOOM) {
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;
				is_exploding_ = true;
				explosion_frame_ = 0;
				explosion_rect_.x = x1 * TILE_SIZE - map_data.start_x_;
				explosion_rect_.y = y1 * TILE_SIZE - map_data.start_y_;
				DecreaseBrain();
			}
			else {
				if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
					x_pos_ = x2 * TILE_SIZE;
					x_pos_ -= width_frame_ + 1;
					x_val_ = 0;
				}
			}
		}
		else if (x_val_ < 0) {
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y2][x1];

			if (val1 == STATE_BRAIN || val2 == STATE_BRAIN) {
				map_data.tile[y1][x1] = 0;
				map_data.tile[y2][x1] = 0;
				IncreateBrain();
			}else if (val1 == STATE_BOOM || val2 == STATE_BOOM) {
				map_data.tile[y1][x1] = 0;
				map_data.tile[y2][x1] = 0;
				is_exploding_ = true;
				explosion_frame_ = 0;
				explosion_rect_.x = x1 * TILE_SIZE - map_data.start_x_;
				explosion_rect_.y = y1 * TILE_SIZE - map_data.start_y_;
				DecreaseBrain();
			}
			else {
				if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
					x_pos_ = (x1 + 1) * TILE_SIZE;
					x_val_ = 0;
				}
			}

		}
	}

	// thang dung

	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

	if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (y_val_ > 0) {
			
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];

			if (val1 == STATE_BRAIN || val2 == STATE_BRAIN) {
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
				IncreateBrain();
			}else if (val1 == STATE_BOOM || val2 == STATE_BOOM) {
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
				is_exploding_ = true;
				explosion_frame_ = 0;
				explosion_rect_.x = x1 * TILE_SIZE - map_data.start_x_;
				explosion_rect_.y = y1 * TILE_SIZE - map_data.start_y_;
				DecreaseBrain();
			}
			else {
				if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
					y_pos_ = y2 * TILE_SIZE;
					y_pos_ -= height_frame_ + 1;
					y_val_ = 0;
					on_ground_ = true;
				}
			}
		}
		else if (y_val_ < 0) {
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];

			if (val1 == STATE_BRAIN || val2 == STATE_BRAIN) {
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
				IncreateBrain();
			}else if (val1 == STATE_BOOM || val2 == STATE_BOOM) {
				map_data.tile[y1][x1] = 0;
				map_data.tile[y1][x2] = 0;
				is_exploding_ = true;
				explosion_frame_ = 0;
				explosion_rect_.x = x1 * TILE_SIZE - map_data.start_x_;
				explosion_rect_.y = y1 * TILE_SIZE - map_data.start_y_;
				DecreaseBrain();
			}
			else {
				if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
					y_pos_ = (y1 + 1) * TILE_SIZE;
					y_val_ = 0;
				}
			}
		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0) {
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > map_data.max_x_) {
		x_pos_ = map_data.max_x_ - width_frame_ - 1;
	}

	if (y_pos_ > map_data.max_y_) {
		if (MessageBox(NULL, L"GAME OVER", L"Info", MB_OK | MB_ICONSTOP) == IDOK) {
			SDL_Delay(500);
			SDL_Quit();
		}
	}
}

void Player::HandleExplosion(SDL_Renderer* screen) {
	if (is_exploding_) {
		explosion_.set_frame(explosion_frame_);
		explosion_.SetRect(explosion_rect_.x, explosion_rect_.y);
		explosion_.Show(screen);

		explosion_frame_++;

		if (explosion_frame_ >= NUM_FRAME_EXP) { 
			is_exploding_ = false;
			explosion_frame_ = 0;
		}
	}
}

void Player::CentreEntityOnMap(Map& map_data) {
	map_data.start_x_ = x_pos_ - (SCREEN_WIDTH / 2);
	if (map_data.start_x_ < 0) {
		map_data.start_x_ = 0;
	}
	else if (map_data.start_x_ + SCREEN_WIDTH >= map_data.max_x_) {
		map_data.start_x_ = map_data.max_x_ - SCREEN_WIDTH;
	}

	map_data.start_y_ = y_pos_ - (SCREEN_HEIGHT / 2);
	if (map_data.start_y_ < 0) {
		map_data.start_y_ = 0;
	}
	else if (map_data.start_y_ + SCREEN_HEIGHT >= map_data.max_y_) {
		map_data.start_y_ = map_data.max_y_ - SCREEN_HEIGHT;
	}
}

void Player::IncreateBrain() {
	brain++;
}
void Player::DecreaseBrain() {
	brain--;
}