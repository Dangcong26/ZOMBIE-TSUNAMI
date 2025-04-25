#ifndef EXP_H_
#define EXP_H_

#include "include.h"
#include "Base.h"

#define NUM_FRAME_EXP 8

class Explosion : public Base {
	public:
		Explosion();
		~Explosion();

		void set_clip();
		void set_frame(const int& fr) {
			frame_ = fr;
		}
		virtual bool LoadImg(string path, SDL_Renderer* screen);
		void Show(SDL_Renderer* screen);
		int get_frame_width() const {
			return frame_width_;
		}
		int get_frame_heigh() const {
			return frame_height_;
		}

private:
	int frame_width_;
	int frame_height_;

	int curr_frame;

	unsigned int frame_;
	SDL_Rect frame_clip_[8];
};
#endif