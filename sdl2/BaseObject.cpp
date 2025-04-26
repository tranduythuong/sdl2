#include"BaseObject.h"
using namespace std;
const int speed = 10;
BaseObject::BaseObject() {
	p_object = NULL;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
	xmove = 0;
	ymove = 0;
}
BaseObject::~BaseObject(){
	Free();
	}
bool BaseObject::LoadImg(string path, SDL_Renderer *renderer) {
	SDL_Texture* newtexture = NULL;
	SDL_Surface* load_surface = IMG_Load(path.c_str());
	if (load_surface != NULL) {
		newtexture = SDL_CreateTextureFromSurface(renderer, load_surface);
		if (newtexture != NULL) {
			rect.w = load_surface->w;
			rect.h = load_surface->h;

		}
		SDL_FreeSurface(load_surface);
	}
	p_object = newtexture;
	return newtexture != NULL;
}
bool BaseObject::LoadImg(SDL_Texture* texture, SDL_Renderer* renderer) {
	if (texture == NULL)return false;
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);
	rect.w = src.w;
	rect.h = src.h;
	p_object = texture;
	return p_object != NULL;
}
void BaseObject::Render(SDL_Renderer* des_renderer,const SDL_Rect* clip) {
	SDL_Rect rectquad = { rect.x,rect.y,rect.w,rect.h };
	SDL_RenderCopy(des_renderer, p_object, clip, &rectquad);
}
void BaseObject::HandInput(SDL_Event& event) {
	if(event.type==SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_UP:
			rect.y -= speed;
			break;
		case SDLK_DOWN:
		    rect.y += speed;
			break;
		case SDLK_RIGHT:
			rect.x += speed;
			break;
		case SDLK_LEFT:
			rect.x -= speed;
			break;
		}
	}
}

void BaseObject::Free() {
	if (p_object != NULL) {
		SDL_DestroyTexture(p_object);
		p_object = NULL;
		rect.w = 0;
		rect.h = 0;
	}
}