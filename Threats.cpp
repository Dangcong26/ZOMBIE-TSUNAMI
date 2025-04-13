#include "Threats.h"

Threats::Threats() {
	width_frame_ = 0;
	height_frame_ = 0;
	x_val_ = 0.0;
	y_val_ = 0.0;
	x_pos_ = 0.0;
	y_pos_ = 0.0;
	on_ground_ = false;
	come_back_time_ = 0;
	frame_ = 0;
	map_x_ = 0; 
	map_y_ = 0; 

	animation_a_ = 0;
	animation_b_ = 0;
	input_type_.left_ = 1;
	type_move_ = STATIC_THREAT;
}

Threats::~Threats() {

}

bool Threats::LoadImg(string path, SDL_Renderer* screen) {
	bool ret = Base::LoadImg(path, screen);

	if (ret) {
		width_frame_ = rect_.w / THREAT_FRAME_NUM;
		height_frame_ = rect_.h;
	}
	return ret;
}

SDL_Rect Threats::GetRectFrame() {
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame_;
	rect.h = height_frame_;

	return rect;
}

void Threats::set_clips() {
	if (width_frame_ > 0 && height_frame_ > 0) {
		for (int i = 0; i < THREAT_FRAME_NUM; i++) {
			frame_clip_[i].x = i * width_frame_;
			frame_clip_[i].y = 0;
			frame_clip_[i].w = width_frame_;
			frame_clip_[i].h = height_frame_;
		}
	}
}

void Threats::Show(SDL_Renderer* des) {
	if (come_back_time_ == 0) {
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;
		frame_++;

		if (frame_ >= THREAT_FRAME_NUM) {
			frame_ = 0;
		}

		SDL_Rect* currentClip = &frame_clip_[frame_];
		SDL_Rect rendQuad = { rect_.x, rect_.y, width_frame_, height_frame_ };
		SDL_RenderCopy(des, p_object_, currentClip, &rendQuad);
	}
}

void Threats::DoPlayer(Map& gMap) {

	if (come_back_time_ > 0) {
		come_back_time_--;
	}
	if (come_back_time_ == 0) {
		x_val_ = 0;
		y_val_ += THREAT_GRAVITY_SPEED;
		if (y_val_ >= THREAT_MAX_FALL_SPEED) {
			y_val_ = THREAT_MAX_FALL_SPEED;
		}

		if (input_type_.left_ == 1) {
			x_val_ -= THREAT_SPEED;
				;
		}
		else if (input_type_.right_ == 1) {
			x_val_ += THREAT_SPEED;
		}

		CheckToMap(gMap);
	}
	else if (come_back_time_ > 0) {
		come_back_time_--;
		if (come_back_time_ == 0) {
			InitThreats();
		}
	}
}

void Threats::InitThreats() {
	x_val_ = 0;
	y_val_ = 0;
	if (x_pos_ > 256) {
		x_pos_ -= 256;
		animation_a_ -= 256;
		animation_b_ -= 256;
	}
	else {
		x_pos_ = 0;
	}
	y_pos_ = 0;
	come_back_time_ = 0;
	input_type_.left_ = 1;
}

void Threats::CheckToMap(Map& gMap) {
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

	x1 = (x_pos_ + x_val_) / TILE_SIZE;
	x2 = (x_pos_ + x_val_ + width_frame_ - 1) / TILE_SIZE;

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_min - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (x_val_ > 0) {
			int val1 = gMap.tile[y1][x2];
			int val2 = gMap.tile[y2][x2];

			if ((val1 != BLANK_TILE && val1 != STATE_BRAIN) || (val2 != BLANK_TILE && val2 != STATE_BRAIN)) {
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= width_frame_ + 1;
				x_val_ = 0;
			}
			//input_type_.left_ = true;
			//input_type_.right_ = false;
		}
		else if (x_val_ < 0) {
			int val1 = gMap.tile[y1][x1];
			int val2 = gMap.tile[y2][x1];

			if ((val1 != BLANK_TILE && val1 != STATE_BRAIN) || (val2 != BLANK_TILE && val2 != STATE_BRAIN)) {
				x_pos_ = (x1 + 1) * TILE_SIZE;
				x_val_ = 0;
			}
			//input_type_.left_ = false;
			//input_type_.right_ = true;
		}
	}

	int width_min = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
	x1 = (x_pos_) / TILE_SIZE;
	x2 = (x_pos_ + width_min) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y) {
		if (y_val_ > 0) {

			int val1 = gMap.tile[y2][x1];
			int val2 = gMap.tile[y2][x2];

			if ((val1 != BLANK_TILE && val1 != STATE_BRAIN) || (val2 != BLANK_TILE && val2 != STATE_BRAIN)) {
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= (height_frame_ + 1);
				y_val_ = 0;
				
				on_ground_ = true;
			}
		}
		else if (y_val_ < 0) {
			int val1 = gMap.tile[y1][x1];
			int val2 = gMap.tile[y1][x2];

			if ((val1 != BLANK_TILE && val1 != STATE_BRAIN) || (val2 != BLANK_TILE && val2 != STATE_BRAIN)) {
				y_pos_ = (y1 + 1) * TILE_SIZE;
				y_val_ = 0;
			}
		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0) {
		x_pos_ = 0;
	}
	else if (x_pos_ + width_frame_ > gMap.max_x_) {
		x_pos_ = gMap.max_x_ - width_frame_ - 1;
	}

	if (y_pos_ > gMap.max_y_) {
		come_back_time_ = 60;
	}
};

void Threats::ImpMoveType(SDL_Renderer* screen) {
	if (type_move_ == STATIC_THREAT) {
		;
	}
	else {
		if (on_ground_ == true) {
			if (x_pos_ > animation_b_) {
				input_type_.left_ = 1;
				input_type_.right_ = 0;
				LoadImg("Threats/threat_left.png", screen);
			}
			else if (x_pos_ < animation_a_) {
				input_type_.left_ = 0;
				input_type_.right_ = 1;
				LoadImg("Threats/threat_right.png", screen);
			}
			else {
				if (input_type_.left_ == 1) {
					LoadImg("Threats/threat_left.png", screen);
				}
			}
		}
	}
}

void Threats::InitBullet(Bullet* p_bullet, SDL_Renderer* screen) {
	if (p_bullet != NULL) {
		p_bullet->LoadImgBullet(screen);
		p_bullet->set_is_move(true);
		p_bullet->set_bullet_dir_(Bullet::DIR_LEFT);
		p_bullet->SetRect(x_pos_ - map_x_ + 5, y_pos_ - map_y_ + 10);
		p_bullet->set_x_val(10);
		bullet_list_.push_back(p_bullet);
	}
}

void Threats::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit) {
	for (int i = 0; i < (int)bullet_list_.size(); i++) {
		Bullet* p_bullet = bullet_list_.at(i);
		if (p_bullet != NULL) {
			if (p_bullet->get_is_move()) {
				int bullet_distance = x_pos_ - map_x_ + width_frame_ - p_bullet->GetRect().x;
				if (bullet_distance <= 320 && bullet_distance > 0) {
					p_bullet->HandleMove(x_limit, y_limit);
					p_bullet->Render(screen);
				}
				else {
					p_bullet->set_is_move(false);
				}
			}
			else {
				p_bullet->set_is_move(true);
				p_bullet->SetRect(x_pos_ - map_x_ + 5, y_pos_ - map_y_ + 10);
			}
		}
	}
}

void Threats::RemoveBullet(const int& idx) {
	int size = bullet_list_.size();
	if (size > 0 && idx < size) {
		Bullet* p_bullet = bullet_list_.at(idx);
		bullet_list_.erase(bullet_list_.begin() + idx);
		if (p_bullet) {
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}

