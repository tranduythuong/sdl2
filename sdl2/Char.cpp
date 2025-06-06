#include"Char.h"

Char::Char() {
	x_val = 0;
	y_val = 0;
	x_pos = 0;
	y_pos = 0;
	width_frame = 0;
	height_frame = 0;
	status = -1;
	frame = 0;
	input_type.left = 0;
	input_type.right = 0;
	input_type.up = 0;
	input_type.down = 0;
	map_x = 0;
	map_y = 0;
	onGround = false;
	level = 1;
}
Char::~Char() {
	
}
void Char::ChartoPortal(Portal& portal, int& level,Uint32 & time_spawn) {
	if (x_pos + width_frame >= portal.getPosX() &&
		x_pos <= portal.getPosX() + portal.getWidth() &&
		y_pos + height_frame >= portal.getPosY() &&
		y_pos <= portal.getPosY() + portal.getHeight())
	{
		level++;
		time_spawn /= 2;
	}
	if (level >= MAX_LEVEL) {
		level = MAX_LEVEL;
	}
}

bool Char::LoadImg(const string path, SDL_Renderer* des) {
	bool ret = BaseObject::LoadImg(path, des);
	if (ret == false) {
		cout << "Khong load duoc img char" << endl;
		
	}
	else {
		width_frame = rect.w / 23;
		height_frame = rect.h;

	}
	return ret;
}
void Char::Show(SDL_Renderer* des) {
	
	if (input_type.right==1||input_type.left==1) {
		
		
		frame++;
	}
	else {
		frame = 0;
	}
	if (frame >= 4) {
		frame = 0;
	}
	
	rect.x = x_pos - map_x;
	rect.y = y_pos - map_y;
	SDL_Rect* clip = &frame_clip[frame];
	SDL_Rect renderQuad = { rect.x,rect.y,width_frame,height_frame };
	SDL_RenderCopy(des, p_object, clip, &renderQuad);
}
void Char::HandleInput(SDL_Event& event, SDL_Renderer* des) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_d:
		{
			status = 1;
			input_type.right = 1;
			input_type.left = 0;
		}
		break;
		case SDLK_a:
		{
			status = 1;
			input_type.left = 1;
			input_type.right = 0;
		}
		break;
		case SDLK_w:
		{
			status = 1;
			input_type.up = 1;
		}

		break;

		}
	}
	else if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_d:
			input_type.right = 0;
			break;
		case SDLK_a:
			input_type.left = 0;
			break;
		case SDLK_w:
			input_type.up = 0;
			break;
		}
	}
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_RIGHT) {
			Bullet *bullet = new Bullet();
			bullet->LoadImg("grf/waterball.png", des);
			bullet->SetRect(x_pos + width_frame / 2, y_pos + height_frame / 2);
			bullet->AngleBullet(x_pos, y_pos, event);
			bullet->set_is_move(true);
			bullet_list.push_back(bullet);	
		}
	}
}
void Char::HandleBullet(SDL_Renderer* des) {
	for (int i = 0; i < bullet_list.size(); i++) {
		Bullet* bullet = bullet_list.at(i);
		if (bullet != NULL) {
			if (bullet->get_is_move() == true) {
				bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				bullet->Render(des);
			}
			else {
				bullet_list.erase(bullet_list.begin() + i);
				if (bullet != NULL) {
					delete bullet;
					bullet = NULL;
				}
			}
		}
	}
}
void Char::RemoveBullet(const int& index) {
	int size = bullet_list.size();
	if (size > 0 && index < size) {
		Bullet* bullet = bullet_list.at(index);
		bullet_list.erase(bullet_list.begin() + index);
		if (bullet != NULL) {
			delete bullet;
			bullet = NULL;
		}
			
	}
}
void Char::set_clips() {
	if (width_frame > 0 && height_frame > 0) {
		for (int i = 0; i < 5; i++) {
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame;
			frame_clip[i].x = i * width_frame;
			frame_clip[i].y = 0;
			
		}
	}
}

void Char::DoPlayer(Map& map,Mix_Chunk * jump,bool & character_fall) {
	
	y_val += FALL_SPEED;
	
	if (y_val >= MAX_FALL_SPEED) {
		y_val = MAX_FALL_SPEED;
	}
	if (input_type.left == 1) {
		x_val =- SPEED;

	}
	else if (input_type.right == 1) {
		x_val = SPEED;
	}
	else {
		x_val = 0;
	}
	if (input_type.up == 1 && onGround == true) {
		y_val = JUMP_SPEED;
		if (!jump) {
			SDL_Log("Failed to load jump sound: %s", Mix_GetError());
		}
		Mix_PlayChannel(-1, jump, 0);
		onGround = false;
	}
	
	
	CheckMap(map,character_fall);
	
}
void Char::CentreEntity(Map& map) {
	map.start_x = x_pos - (SCREEN_WIDTH / 2);
	if (map.start_x < 0) {
		map.start_x = 0;

	}
	map.start_y = y_pos - (SCREEN_HEIGHT / 2);
	if (map.start_y < 0) {
		map.start_y = 0;
	}
	
	
}
void Char::CheckMap(Map& map,bool &character_fall) {
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	
	int height_min = height_frame < TILE_SIZE ? height_frame : TILE_SIZE;
	x1 = (x_pos + x_val) / TILE_SIZE;
	x2 = (x_pos + x_val + width_frame ) / TILE_SIZE;
	y1 = (y_pos ) / TILE_SIZE;
	y2 = (y_pos + height_min-1) / TILE_SIZE;
	if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y) {
		if (x_val > 0) {
			if (map.data[y1][x2] != BLANK_TILE || map.data[y2][x2] != BLANK_TILE) {
				x_pos = x2 * TILE_SIZE - width_frame ;
				x_val = 0;
				
				
			}
		}
		else if(x_val<0){
			if (map.data[y1][x1] != BLANK_TILE || map.data[y2][x1] != BLANK_TILE) {
				x_pos = (x1 +1) * TILE_SIZE;
				x_val = 0;
				
			}
		}
	}

	int width_min = width_frame < TILE_SIZE ? width_frame : TILE_SIZE;
	x1 = (x_pos+1) / TILE_SIZE;
	x2 = (x_pos + width_min-1) / TILE_SIZE;
	
	y1 = (y_pos + y_val) / TILE_SIZE;
	y2 = (y_pos + y_val + height_frame ) / TILE_SIZE;
	if (x1 >= 0 && x2 <= MAX_MAP_X && y1 >= 0 && y2 <= MAX_MAP_Y) {
		if (y_val > 0) {
			if (map.data[y2][x1]!=BLANK_TILE||map.data[y2][x2]!=BLANK_TILE) {
				y_pos = y2 * TILE_SIZE - height_frame ;
				y_val = 0;
				onGround = true;
				
				
			}
		}
		else if(y_val<0){
			if (map.data[y1][x1]!=BLANK_TILE||map.data[y1][x2]!=BLANK_TILE) {
				y_pos = (y1 + 1) * TILE_SIZE;
				y_val = 0;
			}
		}
		
	}
	x_pos += x_val;
	
	y_pos += y_val;
	if (x_pos < 0) {
		x_pos = 0;
	}
	if (x_pos + width_frame >= SCREEN_WIDTH) {
		x_pos = SCREEN_WIDTH - width_frame;
	}
	if (y_pos + height_frame >= SCREEN_HEIGHT) {
		y_pos = SCREEN_HEIGHT - height_frame;
		character_fall = true;
	}
}