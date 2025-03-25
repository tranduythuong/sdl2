#pragma once
#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
using namespace std;
static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;
#define TILE_SIZE 64 
#define MAX_MAP_X 15
#define MAX_MAP_Y 10
struct Map {
	int start_x;
	int start_y;

	int max_x;
	int max_y;

	int data[MAX_MAP_Y][MAX_MAP_X];
	string file_name;
};