#include"MenuAndButton.h"
#include"CommonFunc.h"
MenuAndButton::MenuAndButton() {
	x_pos = 0;
	y_pos = 0;
}

MenuAndButton::~MenuAndButton() {

}
bool MenuAndButton::LoadImg(const string path, SDL_Renderer* des) {
	bool ret = BaseObject::LoadImg(path, des);
	return ret;
}
void MenuAndButton::Show(SDL_Renderer* des) {
	SDL_Rect renderQuad = { x_pos,y_pos, rect.w, rect.h };
	SDL_RenderCopy(des, p_object, NULL, &renderQuad);
}
bool MenuAndButton::HandleMouseEvent(SDL_Event& event,Mix_Chunk* mouse_click) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
		Mix_PlayChannel(-1, mouse_click, 0);
        int x = event.button.x;
        int y = event.button.y;
		if (x >= x_pos && x <= x_pos + rect.w && y >= y_pos && y <= y_pos+ rect.h) {
			return true;
		}
		else {
			return false;
		}
    }
	return false;
}
bool MenuAndButton::HandleOut(SDL_Event& event, Mix_Chunk* mouse_click) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		Mix_PlayChannel(-1, mouse_click, 0);
		int x = event.button.x;
		int y = event.button.y;
		if (x <= x_pos || x >= x_pos + rect.w || y <= y_pos || y >= y_pos + rect.h) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
