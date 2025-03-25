#include"Map.h"
#include "Map.h"



void GameMap::LoadMap(const char* name) {
	ifstream file(name);
	if (!file.is_open()) {
		cout << "Khong the mo file" << endl;
		return;
	}
	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++) {
			file >> game_map.data[i][j];
			int val = game_map.data[i][j];
			
			if (val > 0) {
				if (j > game_map.max_x) { game_map.max_x = j; }
				if (i > game_map.max_y) { game_map.max_y = i; }
			}
		}
	}
	game_map.max_x = (game_map.max_x + 1) * TILE_SIZE;
	game_map.max_y = (game_map.max_y + 1) * TILE_SIZE;
	game_map.start_x = 0;
	game_map.start_y = 0;
	game_map.file_name = name;
	file.close();
}
void GameMap::LoadTiles(SDL_Renderer* renderer,SDL_Texture * tiletex[]) {
	
	for (int i = 0; i < MAX_TILE; i++) {
		bool load=tile_mat[i+1].LoadImg(tiletex[i ], renderer);
		if (load == false) {
			cout << "Khong load duoc tiletexture" << endl;
		}
	}
}
void GameMap::DrawMap(SDL_Renderer* screen) {
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	int map_x = 0;
	int map_y = 0;
	map_x = game_map.start_x / TILE_SIZE;
	map_y = game_map.start_y / TILE_SIZE;
	x1 = (game_map.start_x % TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);
	y1 = (game_map.start_y % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE); 
	for (int i = y1; i < y2; i+=TILE_SIZE) {
		map_x = game_map.start_x / TILE_SIZE;
		for (int j = x1; j < x2; j+=TILE_SIZE) {
			int val = game_map.data[map_y][map_x];
			if (val > 0) {
				tile_mat[val].SetRect(j, i);
				tile_mat[val].Render(screen);
			}
			map_x++;
		}
		map_y++;
	}
}