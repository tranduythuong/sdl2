#pragma once
#include"CommonFunc.h"
using namespace std;

class BaseObject {
public:
	BaseObject();
	~BaseObject();
	void SetRect(const int& x,const  int& y) {
		rect.x = x;
		rect.y = y;
	}
	SDL_Rect GetRect()const {
		return rect;
	}
	SDL_Texture* GetObject()const {
		return p_object;
	}
	 bool LoadImg(std::string path, SDL_Renderer* renderer);
	 bool LoadImg(SDL_Texture* texture, SDL_Renderer* renderer);
	 void Render(SDL_Renderer* des,const SDL_Rect* clip=NULL);
	 void HandInput(SDL_Event& event);
	 void Move();
	 void Free();

protected:
	SDL_Texture *p_object;
	SDL_Rect rect;
	int xmove, ymove;
};