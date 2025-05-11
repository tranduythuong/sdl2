#pragma once
#include"CommonFunc.h"
#include"BaseObject.h"
#include"Map.h"
#include"Portal.h"
#include"Bullet.h"
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
	void ChartoPortal(Portal& portal,int& level,Uint32 & time_spawn);
	bool LoadImg(const string path, SDL_Renderer* des);
	void Show(SDL_Renderer* des);
	void HandleInput(SDL_Event& event,SDL_Renderer * des);
	void HandleBullet(SDL_Renderer* des);	
	void RemoveBullet(const int& index);
	void set_clips();
	void DoPlayer(Map& map,Mix_Chunk *jump,bool & game_running);
	void CheckMap(Map& map,bool& game_running);
	void CentreEntity(Map& map);
	void setPos(int x, int y) {
		x_pos = x;
		y_pos = y;
	}
	int getWidth()const {
		return width_frame;
	}
	int getHeight()const {
		return height_frame;
	}
	int getPosX()const  {
		return x_pos;
	}
	int getPosY()const {
		return y_pos;
	}
	int & getLevel() { 
		return level; 
	}
	void setLevel(int level) {
		this->level = level;
	}
	void set_bullet_list(vector<Bullet*> bulletlist) {
		bullet_list = bulletlist;
	}
	vector<Bullet*> get_bullet_list() const{
		return bullet_list;
	}
private:
	vector<Bullet*> bullet_list;
	int x_val;
	int y_val;
	int x_pos;
	int y_pos;
	int width_frame;
	int height_frame;
	int frame ;
	input input_type;
	SDL_Rect frame_clip[CHAR_FRAME_CLIP];
	int status;
	int map_x;
	int map_y;
	bool onGround;
	int level;
	
};