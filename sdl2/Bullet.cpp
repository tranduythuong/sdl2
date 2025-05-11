#include"Bullet.h"	
Bullet::Bullet() {
	sin = 0;
	cos = 0;
	is_move = false;
}
Bullet::~Bullet() {

}
void Bullet::AngleBullet(int char_xpos, int char_ypos, SDL_Event& event) {
			int x_mouse = event.button.x;
			int y_mouse = event.button.y;
			float delta_x = x_mouse - char_xpos;
			float delta_y = y_mouse - char_ypos;
			float distance = sqrt(delta_x * delta_x + delta_y * delta_y);
			sin =static_cast<float>( delta_y / distance);
			cos = static_cast<float>(delta_x / distance);
}
void Bullet::HandleMove(const int& x, const int& y) {
	rect.x += cos * BULLET_SPEED;
	rect.y += sin * BULLET_SPEED;
	if (rect.x < 0 || rect.x > SCREEN_WIDTH || rect.y < 0 || rect.y > SCREEN_HEIGHT) {
		is_move = false;
	}
}