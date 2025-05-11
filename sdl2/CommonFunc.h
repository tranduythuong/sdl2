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
const int FRAME_PER_SECOND = 60;

#define BULLET_SPEED 20
#define MAX_LEVEL 4
#define RADIAN_FIND_CHARACTER 500
#define MONSTER_SPEED 2
#define CHAR_FRAME_CLIP 23
#define MONSTER_FRAME_CLIPS 2
#define PORTAL_FRAME_CLIPS 5
#define TILE_SIZE 64 
#define MAX_MAP_X 15
#define MAX_MAP_Y 10
#define FALL_SPEED 1
#define JUMP_SPEED -18
#define MAX_FALL_SPEED 10
#define SPEED 5
#define BLANK_TILE 0
#define MAX_TILE 3