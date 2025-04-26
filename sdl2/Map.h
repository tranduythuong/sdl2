#pragma once
#include"CommonFunc.h"
#include"BaseObject.h"

struct Map {
	int start_x;
	int start_y;

	int max_x;
	int max_y;

	int data[MAX_MAP_Y][MAX_MAP_X];
	string file_name;
};
class TileMat :public BaseObject {
public:
	TileMat() { ; }
	~TileMat() { ; }

};
class GameMap {
public:
	GameMap() { ; }
	~GameMap() { ; }
	void LoadMap(const char* name);
	void LoadTiles(SDL_Renderer* renderer, SDL_Texture* filetex[]);
	void DrawMap(SDL_Renderer* renderer);
	Map & getMap() {
		return game_map;
	}
	void getstartXY(int& x, int& y) {
		game_map.start_x = x;
		game_map.start_y = y;
	}
	void setMap(Map& map_data) {
		game_map.start_x = map_data.start_x;
		game_map.start_y = map_data.start_y;
		game_map.file_name = map_data.file_name;
		for (int y = 0; y < MAX_MAP_Y; ++y) {
			for (int x = 0; x < MAX_MAP_X; ++x) {
				game_map.data[y][x] = map_data.data[y][x];
			}
		}
	}
	void setMapLevel(int level);
	

private:
	Map game_map;
	TileMat tile_mat[MAX_TILE];
};