#include"CommonFunc.h"
#include"BaseObject.h"
#include"Map.h"
#include"Char.h"
#include"Time.h"
#include"Portal.h"
#include"Monster.h"
#include"MenuAndButton.h"
#include"HighLevel.h"
#include"Bullet.h"
Uint32 TIME_SPAWN = 3000;
int maplevel = 0;
bool monstertocharacter = false;
bool bullet_to_monster = false;
bool running = true;
bool quit_menu = false;
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
vector<unique_ptr<Monster>> monster_list;
Char character;
HighLevel highlevel;
Mix_Chunk* jump_sound = NULL;
Mix_Music* g_music = NULL;
Mix_Chunk* mouse_click = NULL;
bool character_fall = false;
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
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		SDL_Log("Mix_OpenAudio failed: %s", Mix_GetError());
		success = false;
	}
	if (TTF_Init() == -1) {
		success = false;
	}
	return success;
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
	mouse_click = Mix_LoadWAV("sound/sound_mouse_click.wav");
	if (mouse_click == NULL) {
		SDL_Log("Failed to load mouse click sound: %s", Mix_GetError());
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
	TTF_Quit();
}
void ResetGame() {
	monstertocharacter = false;
	character_fall = false;
	bullet_to_monster = false;
	TIME_SPAWN = 3000;
	maplevel = 0;
	character.setPos(0, 0);
	character.setLevel(1);
	game_map.setMapLevel(0);
	game_map.LoadTiles(g_screen, tiletex);
	fps_time.start();
	monster_list.clear();
}
void game() {
	Mix_PlayMusic(g_music, -1);
	while (!quit_menu) {
		SDL_Event e_event;
		menu_background.Render(g_screen, NULL);
		play_button.Show(g_screen);
		SDL_RenderPresent(g_screen);
		while (SDL_PollEvent(&e_event) != 0) {
			if (e_event.type == SDL_QUIT || play_button.HandleMouseEvent(e_event, mouse_click)) {
				quit_menu = true;
			}
		}
	}
	Uint32 last_time_spawn = 0;
	while (running) {
		highlevel.readHighScore("highscore.txt");
		TTF_Font* font_small = TTF_OpenFont("font.ttf", 24);
		fps_time.start();
		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT) {
				running = false;
			}
			if (pause_button.HandleMouseEvent(g_event, mouse_click)) {
				if (!fps_time.is_paused()) {
					fps_time.paused();
					pause_button.Show(g_screen);
					reverse_button.Show(g_screen);
					if (reverse_button.HandleMouseEvent(g_event, mouse_click)) {
						if (fps_time.is_paused()) {
							fps_time.unpaused();
							ResetGame();
						}
					}
					SDL_RenderPresent(g_screen);
				}
				else {
					fps_time.unpaused();
				}
			}

			if (reverse_button.HandleMouseEvent(g_event, mouse_click)) {
				if (fps_time.is_paused()) {
					fps_time.unpaused();
					ResetGame();
				}
			}
			
			character.HandleInput(g_event, g_screen);
		}
		
		if (monstertocharacter || character_fall) {
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

		portal.set_clips();
		portal.setPos(character.getLevel());
		portal.Show(g_screen);

		character.HandleBullet(g_screen);
		character.set_clips();
		character.ChartoPortal(portal, character.getLevel(),TIME_SPAWN);
		character.DoPlayer(map1, jump_sound, character_fall);
		character.Show(g_screen);

		auto bullet_list = character.get_bullet_list();

		Uint32 current_time = SDL_GetTicks();
		if (current_time >=last_time_spawn + TIME_SPAWN) {
			auto new_monster = make_unique<Monster>();	
			new_monster->LoadImg("grf/Ghosts.png", g_screen);
			new_monster->set_clips();
			new_monster->SetPos();
			monster_list.push_back(move(new_monster));
			last_time_spawn = current_time;
		}
		for (int i = 0; i < monster_list.size();++i) {
			Monster* new_monster = monster_list.at(i).get();
			new_monster->MoveToCharacter(character.getPosX(), character.getPosY(), RADIAN_FIND_CHARACTER);
			new_monster->ChecktoWin(monstertocharacter, character);
			new_monster->Show(g_screen);
			for (int j = 0; j < bullet_list.size();++j) {
				Bullet* bullet = bullet_list.at(j);
				if (bullet != NULL) {
					new_monster->BullettoMonster(bullet_to_monster, bullet);
				}
				if (bullet_to_monster) {
					character.RemoveBullet(j);
					new_monster->Free();
					monster_list.erase(monster_list.begin() + i);
					bullet_to_monster = false;
				}
			}
		}
		if (maplevel != character.getLevel()) {
			game_map.setMapLevel(character.getLevel());
			game_map.LoadTiles(g_screen, tiletex);
			maplevel++;
		}

		highlevel.updateCurrent_Score(character.getLevel());
		highlevel.saveHighScore("highscore.txt");
		highlevel.renderScores(g_screen, font_small);

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
	if (LoadButton() == false) {
		cout << "Failed to load button image" << endl;
		return -1;
	}
	srand(time(0));
	game();
	return 0;
}