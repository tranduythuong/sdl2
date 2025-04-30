#include"Portal.h"
Portal::Portal() {
	x_pos = 0;
	y_pos = 0;
	width_frame = 0;
	height_frame = 0;
	frame = 0;
}
Portal::~Portal() {

}
bool Portal::LoadImg(const string path, SDL_Renderer* des) {
	bool ret = BaseObject::LoadImg(path, des);
	if (ret == false) {
		cout << "Khong load duoc img portal" << endl;
	}
	else {
		width_frame = rect.w / PORTAL_FRAME_CLIPS;
		height_frame = rect.h;
	}
	
	return ret;
}
void Portal::set_clips() {
	if (width_frame > 0 && height_frame > 0) {
		for (int i = 0; i < PORTAL_FRAME_CLIPS; i++) {
			frame_clip[i].x = i * width_frame;
			frame_clip[i].y = 0;
			frame_clip[i].w = width_frame;
			frame_clip[i].h = height_frame;
		}
	}
}

void Portal::Show(SDL_Renderer* des) {
	frame++;
	if (frame >= PORTAL_FRAME_CLIPS) {
		frame = 0;
	}
	rect.x = x_pos;
	rect.y = y_pos;
	SDL_Rect* clip = &frame_clip[frame];
	SDL_Rect renderQuad = { rect.x,rect.y,width_frame,height_frame };
	SDL_RenderCopy(des, p_object, clip, &renderQuad);
}
void Portal::setPos(int& level) {
	if (level == 1) {
		x_pos = 14*TILE_SIZE;
		y_pos = 7*TILE_SIZE;
	}
	if(level==2){
		x_pos = 10 * TILE_SIZE;
		y_pos = 7 * TILE_SIZE;
	}
	if (level == 3) {
		x_pos = 7 * TILE_SIZE;
		y_pos = 5 * TILE_SIZE;
	}
	
}