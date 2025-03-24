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
	brain = 0;
}

Player::~Player() {

}

bool Player::LoadImg(std::string path, SDL_Renderer* screen) {
	bool ret = Base::LoadImg(path, screen);
	
	if (ret == true) {
		width_frame_ = rect_.w / 10;
		height_frame_ = rect_.h;
	}
	return ret;
}

void Player::set_clips() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		frame_clip_[0].x = 0;
		frame_clip_[0].y = 0;
		frame_clip_[0].w = width_frame_;
		frame_clip_[0].h = height_frame_;
		
		frame_clip_[1].x = width_frame_;
		frame_clip_[1].y = 0;
		frame_clip_[1].w = width_frame_;
		frame_clip_[1].h = height_frame_;

		frame_clip_[2].x = 2*width_frame_;
		frame_clip_[2].y = 0;
		frame_clip_[2].w = width_frame_;
		frame_clip_[2].h = height_frame_;

		frame_clip_[3].x = 3 * width_frame_;
		frame_clip_[3].y = 0;
		frame_clip_[3].w = width_frame_;
		frame_clip_[3].h = height_frame_;

		frame_clip_[4].x = 4 * width_frame_;
		frame_clip_[4].y = 0;
		frame_clip_[4].w = width_frame_;
		frame_clip_[4].h = height_frame_;

		frame_clip_[5].x = 5 * width_frame_;
		frame_clip_[5].y = 0;
		frame_clip_[5].w = width_frame_;
		frame_clip_[5].h = height_frame_;

		frame_clip_[6].x = 6 * width_frame_;
		frame_clip_[6].y = 0;
		frame_clip_[6].w = width_frame_;
		frame_clip_[6].h = height_frame_;

		frame_clip_[7].x = 7 * width_frame_;
		frame_clip_[7].y = 0;
		frame_clip_[7].w = width_frame_;
		frame_clip_[7].h = height_frame_;

		frame_clip_[8].x = 8 * width_frame_;
		frame_clip_[8].y = 0;
		frame_clip_[8].w = width_frame_;
		frame_clip_[8].h = height_frame_;

		frame_clip_[9].x = 9 * width_frame_;
		frame_clip_[9].y = 0;
		frame_clip_[9].w = width_frame_;
		frame_clip_[9].h = height_frame_;

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
				map_data.tile[y1][x2] = 0;
				map_data.tile[y2][x2] = 0;
				IncreateBrain();
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
			}
			else {
				if (val1 != BLANK_TILE || val2 != BLANK_TILE) {
					y_pos_ = y2 * TILE_SIZE;
					y_pos_ -= height_frame_ + 1;
					y_val_ = 0;
					on_ground_ = true;
				}
			}

			if (map_data.tile[y2][x1] != BLANK_TILE || map_data.tile[y2][x2] != BLANK_TILE) {
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= height_frame_ + 1;
				y_val_ = 0;
				on_ground_ = true;
			}
		}
		else if (y_val_ < 0) {
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];

			if (val1 = STATE_BRAIN || val2 == STATE_BRAIN) {
				map_data.tile[y2][x1] = 0;
				map_data.tile[y2][x2] = 0;
				IncreateBrain();
			}
			else {
				if (map_data.tile[y1][x1] != BLANK_TILE || map_data.tile[y1][x2] != BLANK_TILE) {
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
		SDL_Delay(500);
		SDL_Quit();
		exit(0);
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