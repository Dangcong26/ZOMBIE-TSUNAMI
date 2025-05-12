#ifndef PLAYER_H_
#define PLAYER_H_

#include "include.h"
#include "Base.h"
#include "Explosion.h"
#include "Sound.h"

#define GRAVITY_SPEED 0.8
#define MAX_FAIL_SPEED 10
#define PLAYER_SPEED 8
#define PLAYER_JUMP_VAL 20

class Player : public Base {
public:
	Player();
	~Player();

	enum WalkType {
		WALK_RIGHT = 0,
		WALK_LEFT = 1,
	};

	virtual bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
	void set_clips();

	void DoPlayer(Map& map_data);
	void CheckToMap(Map& map_data);
	void SetMapXY(const int map_x, const int map_y) {
		map_x_ = map_x;
		map_y_ = map_y;
	};
	void CentreEntityOnMap(Map& map_data);
	void IncreateBrain();
	void DecreaseBrain();
	int Get_Brain() const {
		return brain;
	}

	SDL_Rect GetRectFrame();

	void InitExplosion(SDL_Renderer* screen); 
	void HandleExplosion(SDL_Renderer* screen); 
	bool IsExploding() const { return is_exploding_; } 

	void RandomIncreaseBrain() {
		int randomBonus = rand() % 7 - 3; 
		if (randomBonus > 0) {
			for (int i = 0; i < randomBonus; i++) {
				IncreateBrain();
			}
		}
		else {
			for (int i = randomBonus; i < 0; i++) {
				DecreaseBrain();
			}
		}
	}

	float Get_x_pos() const { return x_pos_;}
	float Get_y_pos() const { return y_pos_;}

	void InitSounds();
	void PlayBulletHitSound();
	void PlayEatBrainSound();
	void PlayHitThreatSound();
	void PlayHitBoomSound();

	void Reset();

	bool IsGameOver() const { return is_game_over_; }
	void SetGameOver(bool game_over) { is_game_over_ = game_over; }


private:
	float x_val_;
	float y_val_;

	float x_pos_;
	float y_pos_;

	int width_frame_;
	int height_frame_;

	SDL_Rect frame_clip_[10];
	Input input_type_;
	int frame_;
	int status_;
	bool on_ground_;

	int map_x_;
	int map_y_;

	int brain;

	Explosion explosion_;
	bool is_exploding_;
	int explosion_frame_;
	SDL_Rect explosion_rect_;

	bool is_game_over_;
};

#endif