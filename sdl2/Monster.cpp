#include"Monster.h"
Monster::Monster() {
	x_val = 0;
	y_val = 0;
	width_frame = 0;
	height_frame = 0;
	frame = 0;
	x_pos = 0;
	y_pos = 0;
	onGround = false;
	map_x = 0;
	map_y = 0;
}
Monster::~Monster() {

}
bool Monster::LoadImg(const string path, SDL_Renderer* des) {
	bool ret = BaseObject::LoadImg(path, des);
	if (ret == false) {
		cout << "Khong load duoc img monster" << endl;
	}
	else {
		width_frame = rect.w / MONSTER_FRAME_CLIPS;
		height_frame = rect.h;
		
	}
	return ret;
}
void Monster::set_clips() {
	if (width_frame > 0 && height_frame > 0) {
		for (int i = 0; i < MONSTER_FRAME_CLIPS; i++) {
			

				frame_clip[i].x = i * width_frame;
				frame_clip[i].y = 0;
				frame_clip[i].w = width_frame;
				frame_clip[i].h = height_frame;
			
		}
	}
	cout << width_frame << " " << height_frame << endl;
}
void Monster::Show(SDL_Renderer* des) {
    frame++;
	if (frame >= 5) {
		frame = 0;
	}

	rect.x = x_pos ;
	rect.y = y_pos ;
	
	SDL_Rect* clip = &frame_clip[frame];
	SDL_Rect renderQuad = { rect.x,rect.y,width_frame,height_frame };
	SDL_RenderCopy(des, p_object, clip, &renderQuad);
}

float Monster::CalculateDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
bool Monster::ChecktoCharacter(int charX, int charY, int detectionRange) {
	float distance = CalculateDistance(this->rect.x, this->rect.y, charX, charY);
	return distance <= detectionRange;
}
void Monster::MoveToCharacter(int charX, int charY,int detectionRange) {
	if (ChecktoCharacter(charX, charY, detectionRange)) {
		int dx = charX - this->x_pos;
		int dy = charY - this->y_pos;	
		if (dx > 0) {
			x_val = MONSTER_SPEED; 
		}
		else if (dx < 0) {
			x_val = -MONSTER_SPEED; 
		}
		else {
			x_val = 0; 
		}

		
		if (dy > 0) {
			y_val = MONSTER_SPEED;
		}
		else if (dy < 0) {
			y_val = -MONSTER_SPEED; 
		}
		else {
			y_val = 0; 
		}
	}
	else {
		
		x_val = 0;
		y_val = 0;
	}
	x_pos += x_val;
	y_pos += y_val;
}

void Monster::ChecktoWin(bool &gamerunning, const Char& character) {
	int x1 = character.getPosX();
	int y1 = character.getPosY();
	int x2 = character.getWidth() + character.getPosX();
	int y2 = character.getHeight() + character.getPosY();
	if (x_val > 0) {
		if ((x_pos + width_frame > x1) && (y_pos < y2 || y_pos + height_frame > y1)) {
			gamerunning = false;
		}
	}
	else {
		if ((x_pos < x2) && (y_pos < y2 || y_pos + height_frame > y1)) {
			gamerunning = false;
		}
	}
}
	void Monster::SetPosLevel(int level) {
		if (level == 0) {
			x_pos = SCREEN_WIDTH-2 * TILE_SIZE;
			y_pos = SCREEN_HEIGHT-2 * TILE_SIZE;
		}
		if (level == 1) {
			x_pos = 5 * TILE_SIZE;
			y_pos = 5 * TILE_SIZE;
		}
		if (level == 2) {
			x_pos = 7 * TILE_SIZE;
			y_pos = 7 * TILE_SIZE;
		}
	}
