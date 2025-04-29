#include"Time.h"
Time::Time() {
	start_tick = 0;
	paused_tick = 0;
	is_start = false;
	is_pause = false;

}
Time::~Time() {

}
void Time::start() {
	is_start = true;
	
	start_tick = SDL_GetTicks();
}
void Time::stop() {
	is_start = false;
	is_pause = false;
}
void Time::paused() {
	if (is_start == true && is_pause == false) {
		is_pause = true;
		paused_tick = SDL_GetTicks() - start_tick;
	}
}
void Time::unpaused() {
	if (is_pause == true) {
		is_pause = false;
		start_tick = SDL_GetTicks() - paused_tick;
		paused_tick = 0;
	}
}
int Time::get_ticks() {
	if (is_start == true) {
		if (is_pause == true) {
			return paused_tick;
		}
		else {
			return SDL_GetTicks() - start_tick;
		}
	}
	return 0;
}
bool Time::is_started() {
	return is_start;
}
bool Time::is_paused() {
	return is_pause;
}