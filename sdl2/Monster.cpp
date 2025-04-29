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
	
}
void Monster::Show(SDL_Renderer* des) {
    frame++;
	if (frame >= MONSTER_FRAME_CLIPS) {
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

void Monster::ChecktoWin(bool& gamerunning, const Char& character) {
	int char_x1 = character.getPosX();
	int char_y1 = character.getPosY();
	int char_x2 = char_x1 + character.getWidth();
	int char_y2 = char_y1 + character.getHeight();

	int mon_x1 = x_pos;
	int mon_y1 = y_pos;
	int mon_x2 = mon_x1 + width_frame;
	int mon_y2 = mon_y1 + height_frame;

	
	bool is_collision =
		!(mon_x2 <= char_x1 || mon_x1 >= char_x2 ||
			mon_y2 <= char_y1 || mon_y1 >= char_y2);

	gamerunning = is_collision;
}

void Monster::SetPos() {
	const int padding = 10;

	int max_x = SCREEN_WIDTH - width_frame - padding;
	int max_y = SCREEN_HEIGHT - height_frame - padding;

	
	x_pos = padding + rand() % (max_x - padding + 1);
	y_pos = padding + rand() % (max_y - padding + 1);
}

