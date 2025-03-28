#pragma once
#include"CommonFunc.h"
#include"BaseObject.h"
class Char :public BaseObject {
public:
	Char();
	~Char();
	void getPos() {
		cout << x_pos << " " << y_pos << endl;
	}
	bool LoadImg(const string path, SDL_Renderer* des);
	void Show(SDL_Renderer* des);
	void HandleInput(SDL_Event& event,SDL_Renderer * des);
	void setclips();
private:
	int x_val;
	int y_val;
	int x_pos;
	int y_pos;
	int width_frame;
	int height_frame;
	int frame = 0;
	SDL_Rect frame_clip[23];
	int status;
};