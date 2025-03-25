#include"RenderWindow.h"
#include<bits/stdc++.h>
using namespace std;
RenderWindow::RenderWindow(const char* windowtiltle, int window_w, int window_h) {
	window = SDL_CreateWindow(windowtiltle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_w, window_h,SDL_WINDOW_SHOWN);
	if (window == NULL) {
		cout << "Khong the khoi tao cua so" << endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}
SDL_Texture* RenderWindow::LoadTexture(const char* path) {
	SDL_Texture* texture=NULL;
	texture = IMG_LoadTexture(renderer, path);
	if (texture == NULL) {
		cout << "NO Load ImgTexture" << endl;
	}
	return texture;
}
void RenderWindow::clearWindow() {
	SDL_DestroyWindow(window);
}
void RenderWindow::clearRenderer() {
	SDL_DestroyRenderer(renderer);
}
void RenderWindow::render(int x, int y, SDL_Texture* p_tex) {
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w;
	src.h;
	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);
	SDL_Rect dtr;
	dtr.x = x;
	dtr.y = y;
	dtr.w = src.w;
	dtr.h = src.h;
	SDL_RenderCopy(renderer, p_tex, &src, &dtr);
}
void RenderWindow::render(float x, float y, const char* path, TTF_Font* font, SDL_Color Fontcolor) {
	SDL_Surface *surface = TTF_RenderText_Blended(font, path, Fontcolor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL) {
		cout << "NO create texture from font" << endl;
	}
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = surface->w;
	src.h = surface->h;
	SDL_Rect dsr;
	dsr.x = x;
	dsr.y = y;
	dsr.w = src.w;
	dsr.h = src.h;
	SDL_RenderCopy(renderer, texture, &src, &dsr);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}
void RenderWindow::renderCenter(float x, float y, const char* path, TTF_Font* font, SDL_Color Fontcolor) {
	SDL_Surface* surface = TTF_RenderText_Blended(font, path, Fontcolor);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w = surface->w;
	src.h = surface->h;
	SDL_Rect drs;
	drs.x = 640 / 2 - src.w / 2 + x;
	drs.y = 480 / 2 - src.h / 2+y;
	drs.w = src.w;
	drs.h = src.h;
	SDL_RenderCopy(renderer, texture, &src, &drs);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}
void RenderWindow::display() {
	SDL_RenderPresent(renderer);
}
void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}
