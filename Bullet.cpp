#include "Bullet.h"

Bullet::Bullet() {
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
}

Bullet::~Bullet() {
	Free();
}

void Bullet::HandleMove(const int& x_border, const int& y_border) {
	if (bullet_dir_ == DIR_RIGHT) {
		rect_.x += x_val_;
		if (rect_.x > x_border) {
			is_move_ = false;
		}
	}
	else if (bullet_dir_ == DIR_LEFT) {
		rect_.x -= x_val_;
		if (rect_.x < 0) {
			is_move_ = false;
		}
	}

}

bool Bullet::LoadImgBullet(SDL_Renderer* des) {
	bool ret = LoadImg("Threats/Bullet.png", des);
	return ret;
}