#pragma once
#include"CommonFunc.h"
class Time {
public:
	Time();
	~Time();
	void start();
	void stop();
	void paused();
	void unpaused();

	int get_ticks();
	
	bool is_started();
	bool is_paused();
	void coutpause() {
		if (is_pause == true) {
			cout << "Paused" << endl;
		}
		else {
			cout << "Unpaused" << endl;
		}
	}
private:
	int start_tick;
	int paused_tick;
	bool is_start;
	bool is_pause;
};