#pragma once
#include"CommonFunc.h"
#include"BaseObject.h"
class Portal:public BaseObject {
public:
	Portal();
	~Portal();
	bool LoadImg(const string path, SDL_Renderer* des);
	void set_clips();
	void Show(SDL_Renderer* des);
	void setPos(int& level);
	int getPosX() { return x_pos; }
	int getPosY() { return y_pos; }
	int getWidth() { return width_frame; }
	int getHeight() { return height_frame; }
	void getPos() {
		cout << x_pos << " P " << y_pos << endl;
	}
private:
	int x_pos;
	int y_pos;
	SDL_Rect frame_clip[4];
	int width_frame;
	int height_frame;
	int frame;
};