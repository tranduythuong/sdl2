#pragma once
#include"CommonFunc.h"

struct HighLevel {
	TTF_Font* font = NULL;
	int high_score;
	int current_score;
	HighLevel() {
		high_score = 0;
		current_score = 0;
	}
	void saveHighScore(const std::string& filename) {
		std::ofstream file(filename);
		if (current_score > high_score) {
			high_score = current_score;
		}
		if (file.is_open()) {
			file << high_score;
		}
	}
	void updateCurrent_Score(int score)  {
		current_score = score;
	}
	int readHighScore(const std::string& filename) {
		std::ifstream file(filename);
		if (file.is_open()) {
			file >> high_score;
			file.close();
		}
		return high_score;
	}
	void renderText( const std::string& text, int x, int y,SDL_Renderer * renderer,TTF_Font * font) {
		if (font == nullptr) {
			SDL_Log("Font is not loaded.");
			return;
		}

		if (text.empty()) {
			SDL_Log("Text is empty, cannot render.");
			return;
		}
		SDL_Color white = { 255,255,255 };
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(),white);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_Rect dst = { x, y, surface->w, surface->h };
		SDL_RenderCopy(renderer, texture, nullptr, &dst);
		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}
	void renderScores(SDL_Renderer* renderer,TTF_Font *font) {
		renderText("Score: " + std::to_string(current_score), SCREEN_WIDTH-2*TILE_SIZE, 0, renderer,font);
		renderText("High Score: " + std::to_string(high_score), SCREEN_WIDTH-2*TILE_SIZE, 30, renderer,font);
	}
};

