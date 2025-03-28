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
}
Char::~Char() {

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
	cout << rect.w << " " << rect.h << endl;
	cout << width_frame << " " << height_frame << endl;
	
	return ret;
}
void Char::Show(SDL_Renderer* des) {
	
	if (status == 1) {
		
		
		frame++;
	}
	else {
		frame = 0;
	}
	if (frame >= 4) {
		frame = 0;
	}
	cout << frame << endl;
	rect.x = x_pos;
	rect.y = y_pos;
	SDL_Rect* clip = &frame_clip[frame];
	SDL_Rect renderQuad = { rect.x,rect.y,width_frame,height_frame };
	SDL_RenderCopy(des, p_object, clip, &renderQuad);
}
void Char::HandleInput(SDL_Event& event, SDL_Renderer* des) {
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_RIGHT:
		{
			status = 1;
			
		}
		break;
		case SDLK_LEFT :
		{
			status = 1;
			
		}
		break;
		}
	}
	else {
		status = -1;
		frame = 0;
	}
}
void Char::setclips() {
	if (width_frame > 0 && height_frame > 0) {
		for (int i = 0; i < 5; i++) {
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame;
			frame_clip[i].x = i * width_frame;
			frame_clip[i].y = 0;
			std::cout << "Frame " << i << ": " << frame_clip[i].x << ", " << frame_clip[i].y << std::endl;
		}
	}
}