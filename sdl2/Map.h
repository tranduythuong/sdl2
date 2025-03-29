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
	void LoadTiles(SDL_Renderer* renderer,SDL_Texture * filetex[]);
	void DrawMap(SDL_Renderer* renderer);
	Map getMap()const {
		return game_map;
	}
private:
	Map game_map;
	TileMat tile_mat[MAX_TILE];
};