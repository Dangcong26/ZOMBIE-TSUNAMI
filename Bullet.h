#ifndef BULLET_H_
#define BULLET_H_


#include "include.h"
#include "Base.h"
 
class Bullet : public Base {
public :
	Bullet();
	~Bullet();

	enum BulletDir {
		DIR_RIGHT = 20,
		DIR_LEFT = 21
	};

	void set_x_val(const int& xval) {
		x_val_ = xval;
	}
	void set_y_val(const int& yval) {
		y_val_ = yval;
	}
	int get_x_val() const {
		return x_val_;
	}
	int get_y_val() const {
		return y_val_;
	}

	void set_is_move(const bool& isMove) {
		is_move_ = isMove;
	}
	bool get_is_move() const {
		return is_move_;
	}

	void set_bullet_dir_(const unsigned int& bulletDir) {
		bullet_dir_ = bulletDir;
	}
	unsigned int get_bullet_dir() const {
		return bullet_dir_;
	}
	void HandleMove(const int& x_border, const int& y_border);
	bool LoadImgBullet(SDL_Renderer* des);
private:
	int x_val_;
	int y_val_;
	bool is_move_;
	unsigned int bullet_dir_;
};


#endif
