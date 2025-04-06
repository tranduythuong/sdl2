#pragma once
#include"CommonFunc.h"
#include"BaseObject.h"
#include"Map.h"
#include"Portal.h"
struct input {
	int right;
	int left;
	int up;
	int down;
	input() {
		right = 0;
		left = 0;
		up = 0;
		down = 0;
	}
};
class Char :public BaseObject {
public:
	Char();
	~Char();
	void ChartoPortal(Portal& portal,int& level);
	bool LoadImg(const string path, SDL_Renderer* des);
	void Show(SDL_Renderer* des);
	void HandleInput(SDL_Event& event,SDL_Renderer * des);
	void setclips();
	void DoPlayer(Map& map);
	void CheckMap(Map& map);
	void CentreEntity(Map& map);
	void setMapXY(const int& x, const int& y) {
		map_x = x;
		map_y = y;
	}
	void getPos() {
		cout << x_pos << " " << y_pos << endl;
	}
	int & getLevel() { 
		return level; 
	}
private:
	int x_val;
	int y_val;
	int x_pos;
	int y_pos;
	int width_frame;
	int height_frame;
	int frame = 0;
	input input_type;
	SDL_Rect frame_clip[23];
	int status;
	int map_x;
	int map_y;
	bool onGround;
	int level;
};