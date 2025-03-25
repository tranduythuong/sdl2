#pragma once
#include"CommonFunc.h"
#include"BaseObject.h"
#define MAX_TILE 20
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
private:
	Map game_map;
	TileMat tile_mat[MAX_TILE];
};