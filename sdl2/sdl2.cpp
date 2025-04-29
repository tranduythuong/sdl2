#include"CommonFunc.h"
#include"BaseObject.h"
#include"Map.h"
#include"Char.h"
#include"Time.h"
#include"Portal.h"
#include"Monster.h"
#include"MenuAndButton.h"
int maplevel = -1;
int monsterlevel = -1;
bool monstertocharacter = false;
bool running = true;
bool game_start = false;
BaseObject g_background;
SDL_Texture* grass = NULL;
SDL_Texture* ground = NULL;
SDL_Texture* tiletex[2] = { grass,ground };
MenuAndButton reverse_button;
MenuAndButton pause_button;
MenuAndButton play_button;
BaseObject menu_background;
GameMap game_map;
Portal portal;
Time fps_time;
Monster monster;
Char character;
Mix_Chunk* jump_sound = NULL;
Mix_Music* g_music = NULL;
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
bool InitAudio() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		SDL_Log("Mix_OpenAudio failed: %s", Mix_GetError());
		return false;
	}
	return true;
}
bool LoadMedia() {
	bool ret = true;
	jump_sound = Mix_LoadWAV("sound/jump.wav");
	if (jump_sound == NULL) {
		SDL_Log("Failed to load jump sound: %s", Mix_GetError());
		ret = false;
	}
	g_music = Mix_LoadMUS("sound/ChiptuneAdventure.mp3");
	if (g_music == NULL) {
		SDL_Log("Failed to load music: %s", Mix_GetError());
		ret = false;
	}
	return ret;
}
bool LoadButton() {
	bool ret = true;
	if (!reverse_button.LoadImg("grf/restart_button.png", g_screen)) {
		ret = false;
	}
	else {
		reverse_button.setPos(SCREEN_WIDTH/2 - reverse_button.getWidth() / 2, SCREEN_HEIGHT/2 - reverse_button.getHeight() / 2);
	}
	if (!pause_button.LoadImg("grf/pause_icon.png", g_screen)) {
		ret = false;
	}
	else {
		pause_button.setPos(0, 0);
	}
	if (!play_button.LoadImg("grf/play_button.png", g_screen)) {
		ret = false;
	}
	else {
		play_button.setPos(SCREEN_WIDTH / 2 - play_button.getWidth() / 2, SCREEN_HEIGHT / 2 - play_button.getHeight() / 2);
	}
	return ret;
}
bool LoadBackground()
{
	menu_background.LoadImg("grf/menu_background.jpg", g_screen);
	bool ret = g_background.LoadImg("grf/background.jpg", g_screen);
	if (ret == false) {
		return false;
	}
	return true;
}
bool LoadTextures() {
	grass = LoadTexture("grf/grass64.png");
	ground = LoadTexture("grf/ground64.png");
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
	Mix_CloseAudio();
	Mix_Quit();  

}
void ResetGame() {
	monstertocharacter = false;
	maplevel = -1;
	monsterlevel = -1;
	character.setPos(0, 0);
	character.setLevel(0);
	monster.SetPos();
	game_map.setMapLevel(0);
	game_map.LoadTiles(g_screen, tiletex);
	fps_time.start();
}
void showMenu() {
	bool inMenu = true;

	while (inMenu) {
		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT) {
				running = false;
				inMenu = false;
				return;
				if (play_button.HandleMouseEvent(g_event)) {
					inMenu = false;
				}
			}


			SDL_SetRenderDrawColor(g_screen, 0, 0, 0, 255);
			SDL_RenderClear(g_screen);
			menu_background.Render(g_screen, NULL);
			play_button.Show(g_screen);
			SDL_RenderPresent(g_screen);
		}
	}
}
void game() {
	monster.set_clips();
	character.set_clips();
	portal.set_clips();
	Mix_PlayMusic(g_music, -1);
	while (running) {
		fps_time.start();
		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT) {
				running = false;
			}
			if (pause_button.HandleMouseEvent(g_event)) {
				if (!fps_time.is_paused()) {
					fps_time.paused();
					pause_button.Show(g_screen);
					SDL_RenderPresent(g_screen);
				}
				else {
					fps_time.unpaused();
				}
			}
			
		    if(reverse_button.HandleMouseEvent(g_event)) {
			    if (fps_time.is_paused()) {
					fps_time.unpaused(); 
					ResetGame();
				}
			}
			
			character.HandleInput(g_event, g_screen);
		}
		
		if (monstertocharacter) {
			fps_time.paused();
			reverse_button.Show(g_screen);
			SDL_RenderPresent(g_screen);
		}
		if (fps_time.is_paused()) {
			continue;
		}
			SDL_SetRenderDrawColor(g_screen, 0, 0, 0, 255);
			SDL_RenderClear(g_screen);
			g_background.Render(g_screen, NULL);

			Map& map1 = game_map.getMap();

			pause_button.Show(g_screen);

			portal.setPos(character.getLevel());
			portal.Show(g_screen);

			character.ChartoPortal(portal, character.getLevel());
			character.DoPlayer(map1,jump_sound);
			character.Show(g_screen);

			if (monsterlevel != character.getLevel()) {
				monster.SetPos();
				monsterlevel++;
			}
			monster.MoveToCharacter(character.getPosX(), character.getPosY(), RADIAN_FIND_CHARACTER);
			monster.ChecktoWin(monstertocharacter, character);
			monster.Show(g_screen);

			if (maplevel != character.getLevel()) {
				game_map.setMapLevel(character.getLevel());
				game_map.LoadTiles(g_screen, tiletex);
				maplevel++;
			}
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
		cout << "Failed to initialize SDL" << endl;
		return -1;
	}
	if(InitAudio() == false) {
		cout << "Failed to initialize audio" << endl;
		return -1;
	}	
	if (LoadMedia() == false) {
		cout << "Failed to load media" << endl;
		return -1;
	}
	if (LoadBackground() == false) {
		cout << "Failed to load background" << endl;
		return -1;
	}
	if (LoadTextures() == false) {
		cout << "Failed to load textures" << endl;
		return -1;
	}
	if (character.LoadImg("grf/char.png", g_screen) == false) {
		cout << "Failed to load character image" << endl;
		return -1;
	}
	if (portal.LoadImg("grf/portal_4.png",g_screen) == false) {
		cout << "Failed to load portal image" << endl;
		return -1;
	}
	if (monster.LoadImg("grf/Ghosts.png", g_screen) == false) {
		cout << "Failed to load monster image" << endl;
		return -1;
	}
	if (LoadButton() == false) {
		cout << "Failed to load button image" << endl;
		return -1;
	}
	srand(time(0));
	showMenu();
	game();
	return 0;
}