#include"CommonFunc.h"
#include"BaseObject.h"
#include"Map.h"
BaseObject g_background;
SDL_Texture* grass = NULL;
SDL_Texture* ground = NULL;
SDL_Texture* tiletex[2] = { grass,ground };
GameMap game_map;

SDL_Texture* LoadTexture(std::string path) {
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == nullptr) {
		std::cout << "Error loading image: " << path << " SDL_image error: " << IMG_GetError() << std::endl;
		return nullptr;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(g_screen, surface);
	SDL_FreeSurface(surface);
	if (texture == nullptr) {
		std::cout << "Error creating texture from " << path << " SDL error: " << SDL_GetError() << std::endl;
	}
	return texture;
}


 bool initData() {
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0) {
		return false;
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == NULL) {
		return false;
	}
	else {
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen == NULL) {
			return false;
		}
		else {
			SDL_SetRenderDrawColor(g_screen, 255, 255, 255, 255);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) && imgFlags)) {
				success= false;
			}
		}
	}
	return success;
}
bool LoadBackground()
{
	bool ret = g_background.LoadImg("C:\\visual studio c++\\code\\sdl2\\grf\\background.jpg", g_screen);
	if (ret == false) {
		return false;
	}
	return true;
}
bool LoadTextures() {
	grass = LoadTexture("C:\\visual studio c++\\code\\sdl2\\grf\\grass64.png");
	ground = LoadTexture("C:\\visual studio c++\\code\\sdl2\\grf\\ground64.png");
	tiletex[0] = grass;
	tiletex[1] = ground;

	return (grass != NULL && ground != NULL);
}
void close() {
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();
}

bool running = false;
void game() {
	game_map.LoadMap("C:\\visual studio c++\\code\\sdl2\\TextFile1.txt");
	game_map.LoadTiles(g_screen, tiletex);
	while (!running) {
		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT) {
				running = true;
			}
		}
		SDL_RenderClear(g_screen);
		g_background.Render(g_screen,NULL);
		game_map.DrawMap(g_screen);
		SDL_RenderPresent(g_screen);
	}
	close();
}
int main(int argc, char* argv[]) {
	if (initData()==false) {
		return -1;
	}
	if (LoadBackground() == false) {
		return -1;
	}
	if (LoadTextures() == false) {
		return -1;
	}
	game();
	return 0;
}
