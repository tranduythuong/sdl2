#pragma once
#include"CommonFunc.h"
#include"BaseObject.h"
class Bullet : public BaseObject {
public:
	Bullet();
	~Bullet();
	void Show(SDL_Renderer* screen);
	void AngleBullet(int char_xpos,int char_ypos, SDL_Event& event);
	void HandleMove(const int& x, const int& y);	
	void set_is_move(bool is_move) { this->is_move = is_move; }
	bool get_is_move() { return is_move; }

private:
	float sin;
	float cos;
	bool is_move;

};