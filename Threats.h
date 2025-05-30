﻿#ifndef THREATS_H_
#define THREATS_H_

#include "include.h"
#include "Base.h"
#include "Bullet.h"
#include "Player.h"

#define THREAT_FRAME_NUM 8
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_MAX_FALL_SPEED 10
#define THREAT_SPEED 3

class Threats : public Base {
public:
	Threats();
	~Threats();

	enum TypeMone {
		STATIC_THREAT = 0,
		MOVE_IN_SPACE_THREAT = 1,
	};

	void set_x_val(const float& xVal) {
		x_val_ = xVal + 8;
	}
	void set_y_val(const float& yVal) {
		y_val_ = yVal;
	}

	void set_x_pos(const float& xp) {
		x_pos_ = xp;
	}
	void set_y_pos(const float& yp) {
		y_pos_ = yp;
	}

	float get_x_pos() const {
		return x_pos_;
	}
	float get_y_pos() const {
		return y_pos_;
	}

	void SetMapXY(const int& mp_x, const int& mp_y) {
		map_x_ = mp_x;
		map_y_ = mp_y;
	}

	void set_clips();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	SDL_Rect GetRectFrame();
	void Show(SDL_Renderer* des);
	int get_width_frame() const {
		return width_frame_;
	}
	int get_height_frame() const {
		return height_frame_;
	}
	void DoPlayer(Map& gMap);
	void CheckToMap(Map& gMap);

	void InitThreats();
	void set_type_move(const int& typeMove) {
		type_move_ = typeMove;
	}
	void SetAnimationPos(const int& pos_a, const int& pos_b) {
		animation_a_ = pos_a;
		animation_b_ = pos_b;
	}
	void set_input_left(const int& ipleft) {
		input_type_.left_ = ipleft;
	}
	void ImpMoveType(SDL_Renderer* screen);

	vector<Bullet*> get_bullet_list() {
		return bullet_list_;
	}
	void set_bullet_list(const vector<Bullet*>& bl_list) {
		bullet_list_ = bl_list;
	}
	void InitBullet(Bullet* p_bullet, SDL_Renderer* screen);
	void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit, float player_x, float player_y);
	void RemoveBullet(const int& idx);


private:

	int map_x_;
	int map_y_;
	float x_val_;
	float y_val_;
	float x_pos_;
	float y_pos_;
	bool on_ground_;
	int come_back_time_;
	SDL_Rect frame_clip_[THREAT_FRAME_NUM];
	int width_frame_;
	int height_frame_;
	int frame_;

	int type_move_;
	int animation_a_;
	int animation_b_;
	Input input_type_;

	vector<Bullet*> bullet_list_;

	int bullet_cooldown_;

};

#endif