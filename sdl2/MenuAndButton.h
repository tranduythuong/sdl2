#pragma once
#include"BaseObject.h"
#include"Time.h"
class MenuAndButton : public BaseObject {
public:
	MenuAndButton();
	~MenuAndButton();
	void setPos(int x, int y) { x_pos = x; y_pos = y; }
	int getWidth() { return rect.w; }
	int getHeight() { return rect.h; }
	void Show(SDL_Renderer* des);
	bool LoadImg(const string path, SDL_Renderer* des);
	bool HandleMouseEvent(SDL_Event& event);
private:
	int x_pos;
	int y_pos;
	
};
