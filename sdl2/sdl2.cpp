#include"CommonFunc.h"
#include"BaseObject.h"
#include"Map.h"
#include"Char.h"
#include"Time.h"
#include"Portal.h"
#include"Monster.h"
int maplevel = -1;
int monsterlevel = -1;
BaseObject g_background;
SDL_Texture* grass = NULL;
SDL_Texture* ground = NULL;
SDL_Texture* tiletex[2] = { grass,ground };
GameMap game_map;
Portal portal;
Time fps_time;
Monster monster;
Char character;
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
				success = false;
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

bool running = true;
void game() {
	monster.set_clips();
	character.set_clips();
	portal.set_clips();	
	while (running) {
		fps_time.start();
		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT) {
				running = false;
			}
			character.HandleInput(g_event, g_screen);
		}
		if(maplevel!=character.getLevel()){
			game_map.setMapLevel(character.getLevel());
			game_map.LoadTiles(g_screen, tiletex);
			maplevel++;
		}
		SDL_SetRenderDrawColor(g_screen, 0, 0, 0, 255);
		SDL_RenderClear(g_screen);
		g_background.Render(g_screen, NULL);
		
		Map  &map1 = game_map.getMap();

		portal.setPos(character.getLevel());
		portal.Show(g_screen);

		character.ChartoPortal(portal, character.getLevel());
		character.DoPlayer(map1);
	    character.Show(g_screen);
		
		if (monsterlevel != character.getLevel()) {
			monster.SetPosLevel(character.getLevel());
			monsterlevel++;
		}
		monster.MoveToCharacter(character.getPosX(), character.getPosY(), RADIAN_FIND_CHARACTER);
		monster.ChecktoWin(running, character);
		monster.Show(g_screen);
		
		game_map.DrawMap(g_screen);
		SDL_RenderPresent(g_screen);
		int real_time = fps_time.get_ticks();
		int time_one_frame = 1000 / FRAME_PER_SECOND;
		if (real_time < time_one_frame) {
			SDL_Delay(time_one_frame - real_time);
		}
	}
	close();
}
int main(int argc, char* argv[]) {
	if (initData() == false) {
		return -1;
	}
	if (LoadBackground() == false) {
		return -1;
	}
	if (LoadTextures() == false) {
		return -1;
	}
	if (character.LoadImg("C:\\visual studio c++\\code\\sdl2\\grf\\char.png", g_screen) == false) {
		cout << "Khong load duoc hinh ảnh char" << endl;
		return -1;
	}
	if (portal.LoadImg("C:\\visual studio c++\\code\\sdl2\\grf\\portal_4.png",g_screen) == false) {
		return -1;
	}
	if (monster.LoadImg("C:\\visual studio c++\\code\\sdl2\\grf\\Ghosts.png", g_screen) == false) {
		return -1;
	}
	game();
	return 0;
}