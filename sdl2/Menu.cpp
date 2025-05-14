#include"Menu.h"
Menu::Menu() {
	x_pos = 0;
	y_pos = 0;
	width_frame = 0;
	height_frame = 0;
	font = NULL;
}
Menu::~Menu() {
	if (font != NULL) {
		TTF_CloseFont(font);
		font = NULL;
	}
}
void Menu::RenderText(int x, int y, SDL_Renderer* renderer, TTF_Font* font){
	if (font == NULL) {
		SDL_Log("Font is not loaded.");
		return;
	}
	if (text.empty()) {
		SDL_Log("Text is empty, cannot render.");
		return;
	}
	SDL_Color white = { 255,255,255 };
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), white);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	width_frame = surface->w;
	height_frame = surface->h;
	x_pos = x;
	y_pos = y;
	SDL_Rect dst = { x_pos, y_pos, width_frame, height_frame };
	SDL_RenderCopy(renderer, texture, nullptr, &dst);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}
bool Menu::HandleMenu(SDL_Event& event,Mix_Chunk * mouse_click) {
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		Mix_PlayChannel(-1, mouse_click, 0);
		int x = event.button.x;
		int y = event.button.y;
		if (x >= x_pos && x <= x_pos + width_frame && y >= y_pos && y <= y_pos + height_frame) {
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}
