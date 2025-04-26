#pragma once
#include"BaseObject.h"
#include"CommonFunc.h"
#include"map.h"
#include"Char.h"
class Monster :public BaseObject {
public:
	Monster();
	~Monster();
	bool LoadImg(const string path, SDL_Renderer* des);
	void set_clips();
	void Show(SDL_Renderer* des);
	void MoveToCharacter(int charX, int charY,int detectionRange);
	bool ChecktoCharacter(int charX, int charY, int detectionRange);
	float CalculateDistance(int x1, int y1, int x2, int y2);
	void SetPosLevel(int level);
	void ChecktoWin(bool& gamerunning,const Char &character);
private:
	int x_start;
	int y_start;
	int x_val;
	int y_val;
	int x_pos;
	int y_pos;
	SDL_Rect frame_clip[MONSTER_FRAME_CLIPS];
	int width_frame;
	int height_frame;
	int frame;
	bool onGround;
	int map_x;
	int map_y;
};