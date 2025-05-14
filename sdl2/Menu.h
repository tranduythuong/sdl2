#pragma once
#include"CommonFunc.h"
class Menu {
public:
	Menu();
	~Menu();
	void RenderText( int x, int y, SDL_Renderer* renderer,TTF_Font *font);
	void RenderMenu(SDL_Renderer* des, TTF_Font* font);
	bool HandleMenu(SDL_Event& event,Mix_Chunk * mouse_click);
	void set_text(const string& a) {
		text = a;
	}
	int getWidth() const {
		return width_frame;
	}
	int getHeight() const {
		return height_frame;
	}
private:
	int x_pos;
	int y_pos;
	int width_frame;
	int height_frame;
	TTF_Font* font;
    string text;
};
